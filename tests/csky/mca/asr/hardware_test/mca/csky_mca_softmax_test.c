#include "hardware_test.h"
#include <assert.h>
#include "csky_mca.h"
#include "csky_vdsp2_nnfunctions.h"
#include "csky_mca_test_helper.h"

static bool test_mca_softmax(mca_num_type_t type);

bool test_mca_softmax_fxp16() {
	return test_mca_softmax(MCA_FXP16);
}

static const size_t INPUT_LEN_ARRAY[] = {
	1, 3, 1024
};
#define INPUT_LEN_ARRAY_SIZE (sizeof(INPUT_LEN_ARRAY) / sizeof(size_t))

static const fxp32_t SAMPLE_INPUT_DATA[] TEST_DATA_ATTR = {
	0xffff2a6f, 0xfff8fcf1, 0x0004888f, 0x000fb586, 0xfff78196, 0xfffca539, 0xfff1eaf0, 0xfffbd7ad,
	0x0007e116, 0xfff4641f, 0xfff57944, 0x000dce27, 0x000491d4, 0x000137ac, 0x000ab607, 0x0007cb81,
	0xfff006ee, 0xfff3fc11, 0x0009ac29, 0x0000d6b8, 0x00084b0a, 0x0008d1e2, 0x000f1683, 0xfff6df3f,
	0x0001dd06, 0xfff8bfdb, 0x00061ca6, 0xfffbdfdb, 0x000b0729, 0x000152b9, 0xfff4e81e, 0x00000d11,
	0x000f93ee, 0x000af0ed, 0x0006a0e5, 0x0004d1b1, 0xfff88820, 0x000b0b3d, 0x0001e985, 0xfff9a7e6,
	0x0007c0a6, 0xfff61402, 0x000f0c2c, 0x0000dbb6, 0xfff35d79, 0xfff49e8d, 0xfff84a38, 0x0009111b,
	0xfff1caea, 0x0003df53, 0x0006e332, 0x00083c31, 0xfff1d23c, 0xfff63179, 0xfff44c08, 0xfff2c1b3,
	0x0001491b, 0xfff673f2, 0x00054f7b, 0x000027d7, 0xfff2d83f, 0x0002b3eb, 0x0004441a, 0xffff0c5b,
	0xfff7ddb8, 0x0005efb9, 0x000437cf, 0x000a426e, 0xfff506ca, 0x00015202, 0x00018531, 0xfff327d8,
	0xfff04cb1, 0xfffea648, 0x000432c0, 0x000c05cc, 0xfffb4314, 0xfffcbf75, 0x0002d10f, 0xfff569da,
	0x0009bce4, 0xfff35c24, 0xfff70ddd, 0x000a421b, 0x00062fa3, 0xfff04eb3, 0xfff1af53, 0x00009c8d,
	0xfff1b587, 0xfff47268, 0x000b0c15, 0xfff8060c, 0xfff2b091, 0xfffda319, 0xfffa436b, 0xfffe6cd4,
	0xfff7ce59, 0x0001bb77, 0xfff69c83, 0xfff2d44a, 0xfffd513d, 0x000ac763, 0x0006d53b, 0xfff46f21,
	0xffff952f, 0xfffdf68d, 0xffffbf06, 0xfff7da2d, 0xfff856fd, 0x0004d86e, 0xfffce741, 0x0001c5ae,
	0xfff3d02b, 0x0006d523, 0xfff08f3e, 0x000cf30e, 0x0001de18, 0xfff688c3, 0xfffbf60a, 0xfff8cf92,
	0xfffda8b8, 0x000370b2, 0xffff7c81, 0x0006237f, 0xfffbace0, 0xfff26d84, 0x0004d028, 0x0001cac2,
	0xfff4ecf1, 0xfff6a934, 0xfff4aa6a, 0xfffb06e4, 0xfffc172f, 0xfffc5ec3, 0xfff820f6, 0xfffe4642,
	0x000e42f8, 0xfffa87ba, 0xfff630ce, 0xfff18917, 0x00089f15, 0x000c9da7, 0xfff3793d, 0xfff3a6a3,
	0x000e3a73, 0x000a5059, 0x0004658e, 0xfff2fb98, 0xfffe2737, 0x000ed395, 0xfffcadea, 0xfff356b8,
	0xfff845c6, 0x000b0cf4, 0xfff1b0ba, 0x000edd42, 0x000b3ea2, 0xfffff371, 0x0000a3d8, 0xfff06a42,
	0x000e81e6, 0xfffd294f, 0x0000b994, 0xfffd8119, 0x0007b4fd, 0x000d42e9, 0xfffaad6b, 0xfffadc05,
	0xfff82369, 0x000836c2, 0x00086bed, 0xfffb549d, 0x00005f7b, 0x000976a0, 0xfffde1d2, 0xfff8fef9,
	0x000819cc, 0xfff0df0a, 0x000938dc, 0x0009b2c1, 0xfff3a478, 0xfffbc101, 0xfff00de0, 0x000b0415,
	0xfffe0135, 0xffff71c6, 0x00070796, 0xfff8d5d5, 0xfff65837, 0xfff3f63b, 0xfff4cc5a, 0x000a6e12,
	0x000cef86, 0xfffe11c8, 0xfffcd4aa, 0x0005a4e6, 0xfffbb1fc, 0xfff96f2b, 0x0008c260, 0xfff9ccf9,
	0x0006f52f, 0xfff22b8f, 0x000e78e9, 0x0008df77, 0xfff3ba92, 0x00048b5c, 0x0006f187, 0xfff09d1a,
	0x000e6220, 0x000632ba, 0x000d2a27, 0xfff812c1, 0x00001b58, 0xfffd5401, 0x000d99bb, 0x0008510e,
	0xfffe6443, 0x000b4c39, 0x00049e67, 0x0007b7ed, 0x000bf47f, 0x000b64e7, 0xfff57053, 0x000aa549,
	0x0008be42, 0xfff6127e, 0x000316da, 0xfff4bb7c, 0xfffb152e, 0xfff2cd95, 0xfff8a9f1, 0xfff05575,
	0x000eae02, 0x000ff257, 0xfffa5c55, 0x000c5f7b, 0x00069c68, 0xfff5ea12, 0x000512ef, 0xfffce372,
	0x000c5d38, 0xfff53f08, 0xfffe6cb2, 0xfffa5319, 0xffff715d, 0x0000a016, 0x000b86cd, 0x0009d883,
	0x0006cf4c, 0xfff5cf73, 0x000f2568, 0xfff6d84b, 0xfff70dee, 0x000ad9cc, 0x0002f898, 0x000b734f,
	0x000857af, 0xfff89590, 0xfff31bbc, 0xfffdbc75, 0x0005e3b4, 0x0008a67b, 0x0006f2d9, 0x00078f04,
	0xfffe08af, 0xffffde22, 0xfffe46f9, 0xfffaf357, 0xfffbc5b8, 0x000ec618, 0xfffba533, 0xfffb09f5,
	0x000f1d4a, 0x0005ae4d, 0xfff3d81f, 0x0006bc1a, 0x000ee262, 0x000bbbb2, 0x000c8f13, 0xfff082f5,
	0xfffa6561, 0x00030769, 0x000ad93f, 0x0008a4a4, 0x0000d561, 0xfffaa944, 0x000b4a5d, 0x000587e0,
	0xfff524ae, 0x0002faa8, 0xfffa9645, 0xfff2e71b, 0xfff634c6, 0x00059309, 0xfffd7637, 0xfffd451a,
	0x000f510f, 0x0006d0a3, 0x0007dba2, 0xfff274fc, 0xffff3da8, 0x00047077, 0xfff32e8c, 0x000903f3,
	0xfffcb84d, 0xfff256b3, 0x000eb132, 0xfffddd95, 0xfff4859f, 0x0003ec08, 0xfffdea2b, 0xfff81f7c,
	0xfff3ca94, 0x0005740a, 0x000a221a, 0xffffd8a6, 0xfffa2adb, 0xfffb9be3, 0xfffbaf51, 0x000e6c80,
	0xfff9cc00, 0xfff37b9d, 0xfffc3e93, 0x000cc2c4, 0x0007bbe6, 0x000bd080, 0x000b90d0, 0x000e8c58,
	0xfff91983, 0x000d2f31, 0xfff8c130, 0xfff5272d, 0x000f9c2f, 0xfff6ebc6, 0x00022c17, 0x00044001,
	0x00031fb6, 0xfffa4a2f, 0xfff2b8aa, 0x00094268, 0x000aee2e, 0x00084389, 0xfffa404a, 0x000abc9e,
	0x0004e49b, 0x00018d4e, 0x00052c74, 0xfff2c927, 0xfff97254, 0x000f9260, 0x00097f66, 0xfff69ba5,
	0x00017b78, 0x0008b5c7, 0x00070b26, 0xfffc115d, 0xfff761c5, 0xfffa4c9b, 0x0005e3f6, 0x00091148,
	0x000514a2, 0xfff1cf9c, 0xfff84064, 0x000d5d78, 0xfff06599, 0x000a9f76, 0xfff2e321, 0xfffbe749,
	0xfff1060f, 0xfff6feda, 0xfff5e9dc, 0x000f9a95, 0xfff3af45, 0x000a6c25, 0x000e21c7, 0xfffa85c5,
	0xfff71949, 0x000cf6c8, 0x000c3874, 0x00036d76, 0xfffe3841, 0x0007ead9, 0x0008aeac, 0x000103fe,
	0x00036480, 0xfff8a889, 0xfff7ccba, 0xfff82cda, 0xfffacd06, 0x00054bd2, 0x000b6bec, 0x000372ab,
	0xfff56772, 0x0000cde7, 0xfffad306, 0x000d4be3, 0x000f9dd4, 0x000a4a16, 0xfffcbdae, 0xfff9dcf3,
	0xffff8454, 0x0009898a, 0xfffbad1f, 0xfff4d45c, 0xfff69faa, 0xfff3977d, 0x00008343, 0x000e80ea,
	0xfff316f0, 0xfff3c987, 0xfff8aa3d, 0xfffd17f6, 0x000d410c, 0x000dc076, 0xfffbc3e7, 0x000dc772,
	0xfff50bc1, 0x000c810a, 0x0007afd4, 0xfffd9181, 0xfffe9262, 0xfffade9d, 0xfff09cce, 0xfff5be18,
	0xfffe90f5, 0x000f0507, 0x000d6055, 0xfff3e7b9, 0x0004ab67, 0xfffda9e8, 0xfff7f45a, 0x00064902,
	0x0001558b, 0xfffe4eb2, 0xfff00b13, 0xfff87bfc, 0x000f125d, 0xfffc3ca1, 0xfffc3625, 0xfff5c4b6,
	0x000b5c20, 0xfff9566e, 0xfff11ca2, 0x00027a77, 0x000b5db8, 0xfff89065, 0xfff5f511, 0x0006970b,
	0x000457cf, 0x0001b477, 0xfff25941, 0xfff0e339, 0xfff62267, 0x00005916, 0x000a09b5, 0xfff46ddc,
	0x000c2f22, 0xfffebeb0, 0xfff7156c, 0xfffc122d, 0xfff0099c, 0xfff160b6, 0x000f59f1, 0xfff58b3e,
	0x000644d7, 0x000ea055, 0x000f899b, 0xfff2fd3c, 0x000eda04, 0xfff90e96, 0xfff0cb4c, 0xfff2f0de,
	0xfff7628d, 0x000a1056, 0x00070500, 0x000eb903, 0xfffa5a04, 0x00090664, 0xfff7b96f, 0xfff03d70,
	0xfff871c8, 0xfff09974, 0x0001cdc5, 0x000fe5de, 0xfff38a03, 0x0005b298, 0x000f8f85, 0xfff23f92,
	0xfffbc77f, 0xfff83140, 0xfff4dcbb, 0xfff0d50b, 0xfff47c4f, 0xfff14cdd, 0xfff6468e, 0x000458ff,
	0x000e2a9f, 0x000a8a31, 0x0007f7d9, 0x000766c7, 0xfffe259c, 0xfff65bf9, 0x0004b9b7, 0x00057aa7,
	0xfff26a1c, 0x0003e3c2, 0x000eb5cb, 0x00022f98, 0xfffd124f, 0x0008fdb0, 0x00098bc1, 0x0004847c,
	0x00051d41, 0xfff11b29, 0xfff42cc5, 0xfff881db, 0x000ec607, 0xfff2ec48, 0x000d1e40, 0xfff9a23d,
	0x00061455, 0xfff2cf8a, 0x000ec3a2, 0x0006cde9, 0x00024b49, 0xfff77d90, 0x000f7a08, 0x00086bf4,
	0x000d3c80, 0x0003bbab, 0x0004dfce, 0x000ab410, 0xfffe87d0, 0xfff48271, 0xfff2d119, 0x000a3b9f,
	0x000d3857, 0xfff7b052, 0xfff88e73, 0xfffb0605, 0xfff7b285, 0xfff92764, 0xfffbe990, 0xfff9d6fe,
	0xfffed49e, 0xfff41fc9, 0x0000bf54, 0x000ad350, 0xfffd2b80, 0x000421c4, 0x000fa967, 0xfff1fc33,
	0x00007a94, 0xfffd19fe, 0xfffca709, 0x000ed5e7, 0xfff2f52f, 0xfffdc1a4, 0xfff08eae, 0x0002f8af,
	0xffff5826, 0x00045c3f, 0xfff769a2, 0x000d167b, 0xfff45bf1, 0x0002d310, 0x000078b9, 0x000dfb90,
	0x000a3a5b, 0x0006468d, 0x000fa610, 0x000ca05f, 0xfffb8534, 0x0002e3b4, 0x000bbe32, 0xfffc4ad6,
	0x000db482, 0xfff6485c, 0x000f269f, 0x0006d8c2, 0x000ba39f, 0x000f9bc5, 0x000a78ed, 0x0006255f,
	0xfffa3a2a, 0xfff43226, 0xfff0f69f, 0x000d9701, 0x0000bc6c, 0xfff425bb, 0x0008050d, 0x0000f614,
	0xfff2aff9, 0xffff222e, 0x000d0ce1, 0xffff178f, 0x000fab74, 0xfffa2066, 0xfff94318, 0x00054d43,
	0xfff22c04, 0x0000eb14, 0xfff62814, 0x000692e9, 0x00097163, 0x00077121, 0xfffd652a, 0x000b5f82,
	0xfff52bb9, 0x000606fc, 0xfff60265, 0x000cd1c6, 0x0001701e, 0x000e8cfb, 0x0002990a, 0xfff1207f,
	0xfff2bc2b, 0xfff74d64, 0xfff3a79b, 0xfff1ae03, 0xfff06de9, 0xfff94bdd, 0xfff3543c, 0xfff0fc20,
	0xfffda7db, 0xfff08930, 0xfff66a90, 0x000cc502, 0xfff9b143, 0xfffeac0b, 0x0007e35e, 0x0005345b,
	0xfff94e49, 0xfffc9b8f, 0xfff99596, 0xffff1117, 0xfff9241d, 0x000e0c31, 0xfff861f8, 0x00047929,
	0xfff26795, 0x000bfacd, 0xfff88c61, 0x00078fe2, 0x000c3fd9, 0xfff2949a, 0xfff1a86d, 0x000b8293,
	0xfff4f0b2, 0xfff38427, 0xfff38bf0, 0xfff5f339, 0xfff4f117, 0xfff25a0d, 0xfff724db, 0xfff34d32,
	0x000c8465, 0xfff0838f, 0x0006dfb5, 0xfff1278e, 0x00087cb7, 0xfffeb494, 0x0009cd8a, 0x000493fa,
	0xfff123db, 0xfff627a7, 0x000f83b1, 0xfff2ca7e, 0x000432a3, 0xffff3968, 0xfff398b1, 0x00039453,
	0x000c623b, 0x00025d9e, 0xfff1a849, 0xfff3d390, 0x0007354b, 0x0005cde5, 0x0005a495, 0xfff05018,
	0x0008e8f0, 0xfffc1abe, 0xfffdb782, 0xfff3bda7, 0x00095c57, 0xfffc74b1, 0xfffd97ad, 0xfff18324,
	0xfffc892b, 0x000a8ee4, 0xfff8b52d, 0x0003070a, 0x0000f060, 0x000026ce, 0x000709f1, 0x0001637e,
	0xfff62240, 0x000f8a29, 0x000145ce, 0xfff9a031, 0xfffe9695, 0xfff035f0, 0x000d9b9f, 0x0004c3a2,
	0x00005031, 0x0000ac41, 0x000a4e5c, 0xfffe40a6, 0xfffd6d13, 0xfff95c32, 0x0009cf5b, 0x000fc63e,
	0x0003c56d, 0xfffda919, 0xfff0daa4, 0xfff752f5, 0x0008ca99, 0x0007aee3, 0x000966f3, 0xfffa24ad,
	0x000a4417, 0x0008b119, 0x000d0de4, 0x000e6379, 0xfff37308, 0xfffdb3b4, 0x0008b7bd, 0x00096ac2,
	0xfff589ae, 0x00019139, 0x000ba612, 0xfff8fd90, 0x0007cf22, 0xfffac7bb, 0xfffd3ff3, 0xfffd0f8f,
	0xfff752b1, 0x0004f205, 0x000a9f7f, 0xfffeda41, 0xfff427f1, 0xfffa40c3, 0xfffab9d3, 0x00018164,
	0xfff99b04, 0x0006e9fb, 0x00016393, 0x000bc21f, 0xfffe8963, 0x0001dd7f, 0xfff8a874, 0x0007cc91,
	0x00095b69, 0xfff74e23, 0xfff4c1f4, 0xfffd9137, 0xfffda00c, 0xfffa7f96, 0x00007533, 0xfff32ff1,
	0xfffbbf06, 0x0002c34a, 0xfff809e5, 0xfff89ca2, 0x00021f26, 0x000bda20, 0xffff0948, 0x000c063c,
	0x000b257b, 0x000bcc85, 0x000d54fe, 0x000ccaa4, 0xfffe989f, 0x0005254c, 0xfffefd48, 0xfffba48a,
	0x000a1cef, 0xfff28100, 0x00026958, 0xfff51b06, 0xfffd0bd6, 0xfffa7183, 0xfffe8552, 0xfff3f33f,
	0xfff5e061, 0x000f3680, 0x00046a77, 0xfff5771d, 0xfff9fe53, 0x00038556, 0xfff1490f, 0xfffa4353,
	0x00080611, 0x000797bc, 0x000887cf, 0xfff0d61b, 0x00082ba4, 0x0002d65e, 0xfff35454, 0xfff9d841,
	0xffff6083, 0xfff77380, 0xfff26c4b, 0x000821d7, 0x000c2eca, 0xfffea50e, 0x000b26fc, 0xfff794f7,
	0xfffafba7, 0xfffddbdd, 0x00036d6d, 0x000b83a4, 0x000fdf4d, 0xfff4e32b, 0x0001e7a0, 0x000f2c4a,
	0x00071c2a, 0x000c3050, 0xfff84ebb, 0x000c227d, 0xfff5b5b4, 0x00046dc0, 0xffff8fa6, 0xfff6f1d3,
	0xfffd97f9, 0xfff8b6fa, 0xfff6ff92, 0xfff1feb5, 0xfffcdab7, 0xfff2ca09, 0x00015110, 0x000cb8a0,
	0xfff8c4e4, 0x000a5f9a, 0x00048a15, 0x00023d9a, 0x000322c5, 0xfff43c92, 0xfff12924, 0x000f81b8,
	0xfff58d77, 0xfff0bca3, 0x000f320d, 0x000ee85d, 0x0006b9b4, 0xfffd1e25, 0x0005b8d5, 0x000b48c1,
	0x00057cd5, 0xfff3ceef, 0xfff6777e, 0xfff362a2, 0x000cea9d, 0x00059654, 0xfffb8c79, 0x00000f42,
	0xffff0a03, 0xfffbd446, 0xfff98783, 0x0006ae31, 0x000bf632, 0x00054e70, 0x000e8406, 0x0002455c,
	0xfff72592, 0xfffab46d, 0xfffab87a, 0xfffaf940, 0x0006197e, 0x0004f7d6, 0x0003dd84, 0x0006de7a,
	0x000b849c, 0xfff17f62, 0xfffb0227, 0x0005ca50, 0xfffa9130, 0x000dc25d, 0x000611f1, 0x000ef90d,
	0x0009cdb3, 0x0007a1e9, 0x0002eb1d, 0xfffc6279, 0xfffb9dbf, 0xffff3294, 0x000f7f00, 0xffff8d21,
	0xfff2cbce, 0x000b0322, 0x00050ad5, 0x00093759, 0xfffa78df, 0xfffc4c05, 0x000a473f, 0x000b7dcf,
	0x0005e586, 0x000ed728, 0xfffe0842, 0xfff03e22, 0xfffccd6f, 0x000108e6, 0x00037a07, 0xfff81a09,
	0xfff68296, 0xfffeb1a3, 0x00044810, 0x00059c09, 0xfffff144, 0xfff41651, 0x000795f5, 0x00010377,
	0x000000c4, 0x0007ab7c, 0xfff2ef1d, 0xfffab23d, 0xfffaf707, 0xfff4e0d1, 0xfff0066b, 0x0005218d,
	0x000e04ee, 0x00084db8, 0x000d59a7, 0xfff04ccd, 0xfff3e44b, 0x0009fa6a, 0xfffb932e, 0xfff5b4e4,
	0xfff55b94, 0x0001c066, 0xfffb38fa, 0xfff15666, 0x0005bc87, 0x000522a6, 0xfff4fa66, 0xfff2499b,
	0xfff3430a, 0xfffde5b8, 0x0006c6eb, 0xfff305c8, 0x000a3f44, 0x0007047c, 0x000aeda4, 0x00083f88,
	0x0004eb20, 0x00032f79, 0x0007b5f6, 0xfff66b74, 0x00078f08, 0xfffa2597, 0x000df887, 0xfff7d981,
	0xfff23fb0, 0xfff6f5fb, 0xfff8be18, 0xfff22d13, 0xfffde62d, 0x000f17c3, 0x0003e354, 0x00003846,
	0x000af5cd, 0x0005fc3d, 0xfff31102, 0x000c1b8b, 0xfffe3d3d, 0x0008451e, 0xfffe7544, 0xfff2e0c2,
	0x0006e231, 0xfffa14a3, 0xffffa540, 0x000bfb16, 0x000f891b, 0x000e58c9, 0x0003c02b, 0x000aa339,
	0x000d99dc, 0xfff6d2b3, 0x000109c2, 0xfffc4a8f, 0x000bbf2d, 0xfffb837b, 0x000fe7e1, 0x000f8126,
	0x000a2bf9, 0xfff54315, 0xfff2c1de, 0x000da5cb, 0x000e58b4, 0x00013013, 0xfffb4c33, 0xfff02354,
	0xfff0c4f7, 0xfffd23cf, 0x000447a2, 0xfffe3f15, 0x0006f22b, 0xfff811b3, 0xfff6ed35, 0xfffaa9fb,
	0xfffdab9c, 0xfffb1f89, 0x00065a84, 0xfffed352, 0xfff3e963, 0xfffba77a, 0xfffd9365, 0x000ba5f1,
	0xfffc57db, 0x000d08b7, 0xfff27db2, 0x0001914e, 0x0006a675, 0xfffa7958, 0x000baeb5, 0x000d37fb,
	0x000b91b1, 0x00033461, 0x0007adea, 0x000bf1c8, 0xfffce49e, 0x000d99d4, 0x000026a7, 0x0004917c,
};

static const fxp16_t GOLDEN_OUTPUT_DATA_1[] /*TEST_DATA_ATTR*/ = {
	0x7fff,
};

static const fxp16_t GOLDEN_OUTPUT_DATA_3[] /*TEST_DATA_ATTR*/ = {
	0x0098, 0x0000, 0x7f69,
};

static const fxp16_t GOLDEN_OUTPUT_DATA_1024[] /*TEST_DATA_ATTR*/ = {
	0x0000, 0x0000, 0x0000, 0x02c6, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x006a, 0x0000, 0x0000, 0x0005, 0x0000,
	0x0000, 0x0000, 0x0002, 0x0000, 0x0000, 0x0001, 0x017d, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0007, 0x0000, 0x0000, 0x0000,
	0x026e, 0x0006, 0x0000, 0x0000, 0x0000, 0x0007, 0x0000, 0x0000,
	0x0000, 0x0000, 0x016e, 0x0000, 0x0000, 0x0000, 0x0000, 0x0001,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0003, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0012, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0002, 0x0000, 0x0000, 0x0003, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0007, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0005, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x002d, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x00a7, 0x0000, 0x0000, 0x0000, 0x0001, 0x0020, 0x0000, 0x0000,
	0x00a1, 0x0003, 0x0000, 0x0000, 0x0000, 0x0126, 0x0000, 0x0000,
	0x0000, 0x0007, 0x0000, 0x0131, 0x0008, 0x0000, 0x0000, 0x0000,
	0x00d5, 0x0000, 0x0000, 0x0000, 0x0000, 0x003d, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0001, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0001, 0x0002, 0x0000, 0x0000, 0x0000, 0x0006,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0004,
	0x002c, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0001, 0x0000,
	0x0000, 0x0000, 0x00ce, 0x0001, 0x0000, 0x0000, 0x0000, 0x0000,
	0x00bc, 0x0000, 0x0038, 0x0000, 0x0000, 0x0000, 0x0056, 0x0000,
	0x0000, 0x0009, 0x0000, 0x0000, 0x0011, 0x0009, 0x0000, 0x0004,
	0x0001, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x00fe, 0x0384, 0x0000, 0x0019, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0019, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x000b, 0x0002,
	0x0000, 0x0000, 0x0194, 0x0000, 0x0000, 0x0006, 0x0000, 0x000a,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0001, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0117, 0x0000, 0x0000,
	0x0188, 0x0000, 0x0000, 0x0000, 0x0137, 0x000d, 0x001e, 0x0000,
	0x0000, 0x0000, 0x0005, 0x0001, 0x0000, 0x0000, 0x0009, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x01df, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0001,
	0x0000, 0x0000, 0x0101, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0003, 0x0000, 0x0000, 0x0000, 0x0000, 0x00c4,
	0x0000, 0x0000, 0x0000, 0x0025, 0x0000, 0x000e, 0x000b, 0x00de,
	0x0000, 0x0039, 0x0000, 0x0000, 0x0283, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0001, 0x0006, 0x0000, 0x0000, 0x0005,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x026b, 0x0001, 0x0000,
	0x0000, 0x0001, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0001,
	0x0000, 0x0000, 0x0000, 0x0044, 0x0000, 0x0004, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x027f, 0x0000, 0x0004, 0x0093, 0x0000,
	0x0000, 0x002e, 0x0016, 0x0000, 0x0000, 0x0000, 0x0001, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x000a, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0040, 0x0287, 0x0003, 0x0000, 0x0000,
	0x0000, 0x0001, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x00d5,
	0x0000, 0x0000, 0x0000, 0x0000, 0x003d, 0x0064, 0x0000, 0x0067,
	0x0000, 0x001d, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0164, 0x0045, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0177, 0x0000, 0x0000, 0x0000,
	0x0009, 0x0000, 0x0000, 0x0000, 0x0009, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0002, 0x0000,
	0x0015, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x01f0, 0x0000,
	0x0000, 0x00f0, 0x0256, 0x0000, 0x012d, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0002, 0x0000, 0x0109, 0x0000, 0x0001, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0359, 0x0000, 0x0000, 0x0264, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0098, 0x0004, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0105, 0x0000, 0x0000, 0x0001, 0x0001, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0116, 0x0000, 0x0035, 0x0000,
	0x0000, 0x0000, 0x0114, 0x0000, 0x0000, 0x0000, 0x0233, 0x0000,
	0x003c, 0x0000, 0x0000, 0x0005, 0x0000, 0x0000, 0x0000, 0x0003,
	0x003b, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0005, 0x0000, 0x0000, 0x02a5, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0128, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0034, 0x0000, 0x0000, 0x0000, 0x007e,
	0x0003, 0x0000, 0x029c, 0x0021, 0x0000, 0x0000, 0x000d, 0x0000,
	0x0060, 0x0000, 0x0196, 0x0000, 0x000c, 0x0282, 0x0004, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0055, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0032, 0x0000, 0x02aa, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0001, 0x0000, 0x0000, 0x0009,
	0x0000, 0x0000, 0x0000, 0x0027, 0x0000, 0x00df, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0026, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0087, 0x0000, 0x0000,
	0x0000, 0x0011, 0x0000, 0x0000, 0x0016, 0x0000, 0x0000, 0x000b,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x001d, 0x0000, 0x0000, 0x0000, 0x0001, 0x0000, 0x0002, 0x0000,
	0x0000, 0x0000, 0x0248, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x001a, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0001, 0x0000, 0x0000, 0x0000, 0x0001, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0004, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0257, 0x0000, 0x0000, 0x0000, 0x0000, 0x0057, 0x0000,
	0x0000, 0x0000, 0x0003, 0x0000, 0x0000, 0x0000, 0x0002, 0x02f6,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0001, 0x0000, 0x0001, 0x0000,
	0x0003, 0x0001, 0x0032, 0x00bd, 0x0000, 0x0000, 0x0001, 0x0001,
	0x0000, 0x0000, 0x000c, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0004, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x000e, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0001, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x000f, 0x0000, 0x0012,
	0x0007, 0x000e, 0x0042, 0x0026, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0003, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x01b0, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0001, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0015, 0x0000, 0x0007, 0x0000,
	0x0000, 0x0000, 0x0000, 0x000b, 0x0343, 0x0000, 0x0000, 0x019f,
	0x0000, 0x0015, 0x0000, 0x0014, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0024,
	0x0000, 0x0003, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0244,
	0x0000, 0x0000, 0x01a9, 0x013e, 0x0000, 0x0000, 0x0000, 0x0009,
	0x0000, 0x0000, 0x0000, 0x0000, 0x002b, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0011, 0x0000, 0x00d7, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x000b, 0x0000, 0x0000, 0x0000, 0x0000, 0x0065, 0x0000, 0x0154,
	0x0002, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x023e, 0x0000,
	0x0000, 0x0006, 0x0000, 0x0001, 0x0000, 0x0000, 0x0003, 0x000a,
	0x0000, 0x012a, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0083, 0x0000, 0x0043, 0x0000, 0x0000, 0x0002, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0003, 0x0000, 0x0006, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x007d, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x017f, 0x0000, 0x0000,
	0x0006, 0x0000, 0x0000, 0x0013, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0011, 0x0255, 0x00b6, 0x0000, 0x0004,
	0x0056, 0x0000, 0x0000, 0x0000, 0x000d, 0x0000, 0x0360, 0x0242,
	0x0003, 0x0000, 0x0000, 0x005a, 0x00b6, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x000c,
	0x0000, 0x0031, 0x0000, 0x0000, 0x0000, 0x0000, 0x000d, 0x003b,
	0x000b, 0x0000, 0x0000, 0x0010, 0x0000, 0x0056, 0x0000, 0x0000,
};

static const fxp16_t *const GOLDEN_OUTPUT_DATA[] = {
	GOLDEN_OUTPUT_DATA_1,
	GOLDEN_OUTPUT_DATA_3,
	GOLDEN_OUTPUT_DATA_1024
};

typedef struct {
	const fxp32_t *raw_input;
	const fxp16_t *raw_output;
} mca_softmax_test_params;

static void gen_mca_softmax_golden_data(
	void *params,
	const mca_cache_block_t *cache_blocks,
	void **cache_ptrs);

static bool test_mca_softmax_kernal(
	void *params,
	const mca_test_block_t *test_blocks,
	void **block_ptrs);

// Maximal tolerance for MCA SoftMax
// There would be error for q24 output. But for 8-bit and 16-bit, there should
// be no error.
static const fxp32_t MAX_MCA_SOFTMAX_TOL = 0;

bool test_mca_softmax(mca_num_type_t type) {
	bool total_passed = true, passed;

	for (size_t i = 0; i < INPUT_LEN_ARRAY_SIZE; ++i) {
		mca_cache_block_t cache_blocks[] = {
			// Input
			{
				.type = MCA_FXP32,
				.count = INPUT_LEN_ARRAY[i],
			},
			// Output
			{
				.type = type,
				.count = INPUT_LEN_ARRAY[i],
			},
		};

		mca_test_block_t test_blocks[] = {
			// Input
			{
				.type = MCA_FXP32,
				.count = INPUT_LEN_ARRAY[i],
				.aligns = align_0,
				.io_dir = io_dir_input,
				.cache_index = 0,
				.input_change_allowed = true,
			},
			// Output
			{
				.type = type,
				.count = INPUT_LEN_ARRAY[i],
				.aligns = align_0,
				.io_dir = io_dir_output,
				.cache_index = 1,
				.tolerance = MAX_MCA_SOFTMAX_TOL,
			},
		};

		mca_softmax_test_params params = {
			.raw_input = SAMPLE_INPUT_DATA,
			.raw_output = GOLDEN_OUTPUT_DATA[i],
		};

		passed = mca_generic_hardware_test(
			&params,
			gen_mca_softmax_golden_data,
			cache_blocks,
			sizeof(cache_blocks) / sizeof(cache_blocks[0]),
			test_mca_softmax_kernal,
			test_blocks,
			sizeof(test_blocks) / sizeof(test_blocks[0]));

		if (!passed) {
			print_log("Failed for input size %d.\n", INPUT_LEN_ARRAY[i]);
			total_passed = false;
		}
	}

	return total_passed;
}

void gen_mca_softmax_golden_data(
	void *params,
	const mca_cache_block_t *cache_blocks,
	void **cache_ptrs) {
	mca_softmax_test_params *tp = params;

	const mca_cache_block_t *input_block = &cache_blocks[0];
	const mca_cache_block_t *output_block = &cache_blocks[1];

	void *input_ptr = cache_ptrs[0];
	void *output_ptr = cache_ptrs[1];

	asr_memcpy(input_ptr, tp->raw_input,
		size_of(input_block->type) * input_block->count);

	switch (output_block->type) {
	case MCA_FXP32:
		for (size_t i = 0; i < input_block->count; ++i) {
			((fxp32_t *)output_ptr)[i] = tp->raw_output[i];
		}
		break;
	case MCA_FXP16:
		memcpy(output_ptr, tp->raw_output,
			size_of(output_block->type) * output_block->count);
		break;
	default:
		ASR_ASSERT("Not implemented");
		break;
	}
}

bool test_mca_softmax_kernal(
	void *params,
	const mca_test_block_t *test_blocks,
	void **block_ptrs) {
	const mca_test_block_t *output_block = &test_blocks[1];

	fxp32_t *input_ptr = block_ptrs[0];
	void *output_ptr = block_ptrs[1];

	switch (output_block->type) {
	case MCA_FXP16:
		csky_mca_softmax_fxp16(input_ptr, output_ptr, output_block->count);
		break;
	default:
		ASR_ASSERT("Not implemented");
		break;
	}

	return true;
}
