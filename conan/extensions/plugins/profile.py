# This file was generated by Conan. Remove this comment if you edit this file or Conan
# will destroy your changes.

def profile_plugin(profile):
    settings = profile.settings
    if settings.get("compiler") in ("msvc", "clang") and settings.get("compiler.runtime"):
        if settings.get("compiler.runtime_type") is None:
            runtime = "Debug" if settings.get("build_type") == "Debug" else "Release"
            try:
                settings["compiler.runtime_type"] = runtime
            except ConanException:
                pass
    _check_correct_cppstd(settings)
    _check_correct_cstd(settings)


def _check_correct_cppstd(settings):
    cppstd = settings.get("compiler.cppstd")
    version = settings.get("compiler.version")

    if cppstd and version:
        compiler = settings.get("compiler")
        from conan.tools.build.cppstd import supported_cppstd
        supported = supported_cppstd(None, compiler, version)
        # supported is None when we don't have information about the compiler
        # but an empty list when no flags are supported for this version
        if supported is not None and cppstd not in supported:
            from conan.errors import ConanException
            raise ConanException(f"The provided compiler.cppstd={cppstd} is not supported by {compiler} {version}. "
                                 f"Supported values are: {supported}")


def _check_correct_cstd(settings):
    cstd = settings.get("compiler.cstd")
    version = settings.get("compiler.version")

    if cstd and version:
        compiler = settings.get("compiler")
        from conan.tools.build.cstd import supported_cstd
        supported = supported_cstd(None, compiler, version)
        # supported is None when we don't have information about the compiler
        # but an empty list when no flags are supported for this version
        if supported is not None and cstd not in supported:
            from conan.errors import ConanException
            raise ConanException(f"The provided compiler.cstd={cstd} is not supported by {compiler} {version}. "
                                 f"Supported values are: {supported}")
