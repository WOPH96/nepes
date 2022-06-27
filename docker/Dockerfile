FROM woph96/xq:zsh
ENV LC_ALL=C.UTF-8

# Install Miniconda
ENV LANG=C.UTF-8 LC_ALL=C.UTF-8
ENV PATH /opt/conda/bin:$PATH
RUN apt-get update && apt-get -qq -y install bzip2 ca-certificates build-essential libusb-1.0-0-dev udev usbutils \
	&& curl -sSL https://repo.anaconda.com/miniconda/Miniconda3-py37_4.12.0-Linux-aarch64.sh -o /tmp/miniconda.sh \
	&& bash /tmp/miniconda.sh -bfp /usr/local \
    && rm -rf /tmp/miniconda.sh \
    && conda install -y python=3.7 \
    && conda update conda \
	&& apt-get -qq -y autoremove \
    && apt-get autoclean \
    && rm -rf /var/lib/apt/lists/* /var/log/dpkg.log \
    && conda clean --all --yes \
	&& conda install tensorflow
RUN pip install keras==2.5.0rc0 pandas==1.3.5 Pillow==9.1.1 matplotlib==3.5.2 \
	&& cd && mkdir xq && mv xenqore* xq \
	&& cp -r ~/xq/xenqore_v1.4/xenqore /usr/local/lib/python3.7/site-packages/ \
	&& cp ~/xq/xenqore-cpp/lib/linux.aarch64/libxenqore.so.1.0.0 /usr/local/lib \
	&& ln -s /usr/local/lib/libxenqore.so.1.0.0 /usr/local/lib/libxenqore.so  \
	&& echo "export LD_LIBRARY_PATH=/usr/local/lib" >> ~/.zshrc \
	&& mkdir -p /etc/udev/rules.d && touch /etc/udev/rules.d/xenqore.rules \
	&& echo "SUBSYSTEM='usb', ATTRS{idProduct}=='000a', ATTRS{idVendor}=='04b4', MODE='0666', group='users'" >> /etc/udev/rules.d/xenqore.rules \
	&& echo "SUBSYSTEM='usb', ATTRS{idProduct}=='1003', ATTRS{idVendor}=='04b4', MODE='0666', group='users'" >> /etc/udev/rules.d/xenqore.rules \
	&& echo "SUBSYSTEM='usb', ATTRS{idProduct}=='00f1', ATTRS{idVendor}=='04b4', MODE='0666', group='users'" >> /etc/udev/rules.d/xenqore.rules 

#RUN udevadm control --reload
