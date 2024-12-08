FROM ubuntu:24.10

# Install basic dependencies
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    clang \
    git \
    libboost-all-dev \
    libssl-dev \
    gdb \
    curl \
    vim \
    zsh \
    wget \
    sudo \
    && apt-get clean

# Set up a default non-root user (optional)
ARG USERNAME=vscode
ARG USER_UID=1001
RUN groupadd $USERNAME \
    && useradd --uid $USER_UID --gid $(getent group $USERNAME | cut -d: -f3) -m $USERNAME \
    && echo "$USERNAME ALL=(ALL) NOPASSWD:ALL" > /etc/sudoers.d/$USERNAME \
    && chmod 0440 /etc/sudoers.d/$USERNAME

# Install Oh My Zsh
USER $USERNAME
RUN sh -c "$(curl -fsSL https://raw.githubusercontent.com/ohmyzsh/ohmyzsh/master/tools/install.sh)"

# Set up workspace directory
WORKDIR /workspaces/blog

# Configure .zshrc (optional - custom theme or plugins)
RUN echo "\
ZSH_THEME=\"agnoster\"\n\
plugins=(git)\n\
source \$ZSH/oh-my-zsh.sh\n\
" > /home/$USERNAME/.zshrc

# Ensure proper permissions for the user
RUN sudo chown -R $USERNAME:$USERNAME /home/$USERNAME

# Set default shell to zsh
SHELL ["/bin/zsh", "-c"]