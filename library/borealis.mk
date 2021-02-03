mkfile_path	:=	$(abspath $(lastword $(MAKEFILE_LIST)))
current_dir	:=	$(BOREALIS_PATH)/$(notdir $(patsubst %/,%,$(dir $(mkfile_path))))

LIBS		:=	-lglfw3 -lEGL -lglapi -ldrm_nouveau -lm $(LIBS)

include $(TOPDIR)/$(current_dir)/lib/extern/switch-libpulsar/deps.mk

# TODO: remove /lib/platforms/glfw from Switch makefile as it's PC only
SOURCES		:=	$(SOURCES) \
				$(current_dir)/lib/core \
				$(current_dir)/lib/views \
				$(current_dir)/lib/touch \
				$(current_dir)/lib/platforms/glfw \
				$(current_dir)/lib/platforms/switch \
				$(current_dir)/lib/extern/glad \
				$(current_dir)/lib/extern/nanovg \
				$(current_dir)/lib/extern/libretro-common/compat \
				$(current_dir)/lib/extern/libretro-common/encodings \
				$(current_dir)/lib/extern/libretro-common/features \
				$(current_dir)/lib/extern/nxfmtwrapper \
				$(current_dir)/lib/extern/yoga/src/yoga/event \
				$(current_dir)/lib/extern/yoga/src/yoga \
				$(current_dir)/lib/extern/tinyxml2/ \
				$(addprefix $(current_dir)/lib/extern/switch-libpulsar/, $(PLSR_SOURCES))

INCLUDES	:=	$(INCLUDES) \
				$(current_dir)/include \
				$(current_dir)/lib/extern/fmt/include \
				$(current_dir)/lib/extern/yoga/src \
				$(current_dir)/include/borealis/extern \
				$(current_dir)/include/borealis/extern/tinyxml2 \
				$(addprefix $(current_dir)/lib/extern/switch-libpulsar/, $(PLSR_INCLUDES))

CXXFLAGS := $(CXXFLAGS) -DYG_ENABLE_EVENTS
