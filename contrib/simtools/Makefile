SDKHOME ?= /opt/netronome
SDK_INC=$(SDKHOME)/include
SDK_LIB=$(SDKHOME)/lib

TARGETS= 								\
	sim_imb_setup sim_nbi_dma_setup sim_nbi_pre_setup		\
	sim_nbi_tm_setup sim_mac_setup sim_pcap_record sim_pcap_play 	\
	sim_me_reset sim_step nfp_imem nfp_emem nfp_ctm nfp_cls nfp_lmem\
	mb_dump rtsym

all: $(TARGETS)

sim_imb_setup: sim_imb_setup.c
	gcc -g -o sim_imb_setup sim_imb_setup.c -I$(SDK_INC) -L$(SDK_LIB) \
		-lpcap -lnfp -lnfp_cpp -lnfp_sal -lrt -lnfp_resid -lns_log

sim_nbi_dma_setup: sim_nbi_dma_setup.c
	gcc -g -o sim_nbi_dma_setup sim_nbi_dma_setup.c -I$(SDK_INC) \
		-L$(SDK_LIB) -lpcap -lnfp -lnfp_cpp -lnfp_sal -lrt \
		-lnfp_resid -lns_log

sim_nbi_pre_setup: sim_nbi_pre_setup.c
	gcc -g -o sim_nbi_pre_setup sim_nbi_pre_setup.c -I$(SDK_INC) \
		-L$(SDK_LIB) -lpcap -lnfp -lnfp_cpp -lnfp_sal -lrt \
		-lnfp_resid -lns_log

sim_mac_setup: sim_mac_setup.c
	gcc -g -o sim_mac_setup sim_mac_setup.c -I$(SDK_INC) -L$(SDK_LIB) \
		-lpcap -lnfp -lnfp_cpp -lnfp_sal -lrt -lnfp_resid -lns_log

sim_nbi_tm_setup: sim_nbi_tm_setup.c
	gcc -g -o sim_nbi_tm_setup sim_nbi_tm_setup.c -I$(SDK_INC) -L$(SDK_LIB)\
		-lpcap -lnfp -lnfp_cpp -lnfp_sal -lrt -lnfp_resid -lns_log

sim_pcap_record: sim_pcap_record.c
	gcc -g -o sim_pcap_record sim_pcap_record.c -I$(SDK_INC) -L$(SDK_LIB) \
		-lpcap -lnfp -lnfp_cpp -lnfp_sal -lrt -lnfp_resid -lns_log

sim_pcap_play: sim_pcap_play.c
	gcc -g -o sim_pcap_play sim_pcap_play.c -I$(SDK_INC) -L$(SDK_LIB) \
		-lpcap -lnfp -lnfp_cpp -lnfp_sal -lrt -lnfp_resid -lns_log

sim_me_reset: sim_me_reset.c 
	gcc -g -o sim_me_reset sim_me_reset.c \
		-I$(SDK_INC) -L$(SDK_LIB) -lnfp -lnfp_sal -lpthread -lns_log

sim_step: sim_step.c 
	gcc -g -o sim_step sim_step.c \
		-I../../include -I. -I$(SDK_INC) -L$(SDK_LIB) -lnfp -lpthread \
		-lnfp_sal -lns_log

nfp_imem: nfp_imem.c 
	gcc -g -o nfp_imem nfp_imem.c \
		-I../../include -I. -I$(SDK_INC) -L$(SDK_LIB) -lnfp -lpthread \
		-lns_log

nfp_emem: nfp_emem.c 
	gcc -g -o nfp_emem nfp_emem.c \
		-I../../include -I. -I$(SDK_INC) -L$(SDK_LIB) -lnfp -lpthread \
		-lns_log

nfp_ctm: nfp_ctm.c 
	gcc -g -o nfp_ctm nfp_ctm.c \
		-I../../include -I. -I$(SDK_INC) -L$(SDK_LIB) -lnfp -lpthread \
		-lns_log

nfp_cls: nfp_cls.c 
	gcc -g -o nfp_cls nfp_cls.c \
		-I../../include -I. -I$(SDK_INC) -L$(SDK_LIB) -lnfp -lpthread \
		-lns_log

nfp_lmem: nfp_lmem.c 
	gcc -g -o nfp_lmem nfp_lmem.c \
		-I../../include -I. -I$(SDK_INC) -L$(SDK_LIB) -lnfp -lnfp_resid \
		-lpthread -lns_log

mb_dump: mb_dump.c 
	gcc -g -o mb_dump mb_dump.c \
		-I$(SDK_INC) -L$(SDK_LIB) -lnfp -lnfp_sal -lpthread -lns_log

rtsym: rtsym.c 
	gcc -g -o rtsym rtsym.c \
		-I../../include -I. -I$(SDK_INC) -L$(SDK_LIB) -lnfp -lpthread \
		-lnfp_sal -lns_log

clean:
	rm -f $(TARGETS)
