xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 183;
 0.00000;40.53390;0.00000;,
 10.33410;41.51720;-10.33410;,
 0.00000;41.51720;-14.61470;,
 0.00000;40.53390;0.00000;,
 14.61470;41.51720;0.00000;,
 0.00000;40.53390;0.00000;,
 10.33410;41.51720;10.33410;,
 0.00000;40.53390;0.00000;,
 0.00000;41.51720;14.61470;,
 0.00000;40.53390;0.00000;,
 -10.33410;41.51720;10.33410;,
 0.00000;40.53390;0.00000;,
 -14.61470;41.51720;0.00000;,
 0.00000;40.53390;0.00000;,
 -10.33410;41.51720;-10.33410;,
 0.00000;40.53390;0.00000;,
 0.00000;41.51720;-14.61470;,
 19.09500;33.23860;-19.09500;,
 0.00000;33.23860;-27.00440;,
 27.00440;33.23860;0.00000;,
 19.09500;33.23860;19.09500;,
 0.00000;33.23860;27.00440;,
 -19.09500;33.23860;19.09500;,
 -27.00440;33.23860;0.00000;,
 -19.09500;33.23860;-19.09500;,
 0.00000;33.23860;-27.00440;,
 24.94880;20.84890;-24.94880;,
 0.00000;20.84890;-35.28300;,
 35.28300;20.84890;0.00000;,
 24.94880;20.84890;24.94880;,
 0.00000;20.84890;35.28300;,
 -24.94880;20.84890;24.94880;,
 -35.28300;20.84890;0.00000;,
 -24.94880;20.84890;-24.94880;,
 0.00000;20.84890;-35.28300;,
 27.00440;6.23420;-27.00440;,
 0.00000;6.23420;-38.19000;,
 38.19000;6.23420;0.00000;,
 27.00440;6.23420;27.00440;,
 0.00000;6.23420;38.19000;,
 -27.00440;6.23420;27.00440;,
 -38.19000;6.23420;0.00000;,
 -27.00440;6.23420;-27.00440;,
 0.00000;6.23420;-38.19000;,
 24.94880;1.62417;-24.94880;,
 0.00000;1.62417;-35.28300;,
 35.28300;1.62417;0.00000;,
 24.94880;1.62417;24.94880;,
 0.00000;1.62417;35.28300;,
 -24.94880;1.62417;24.94880;,
 -35.28300;1.62417;0.00000;,
 -24.94880;1.62417;-24.94880;,
 0.00000;1.62417;-35.28300;,
 19.09500;-7.51377;-19.09500;,
 0.00000;-7.51377;-27.00440;,
 27.00440;-7.51377;-0.00000;,
 19.09500;-7.51377;19.09500;,
 0.00000;-7.51377;27.00440;,
 -19.09500;-7.51377;19.09500;,
 -27.00440;-7.51377;0.00000;,
 -19.09500;-7.51377;-19.09500;,
 0.00000;-7.51377;-27.00440;,
 10.33410;-15.79236;-10.33410;,
 0.00000;-15.79236;-14.61470;,
 14.61470;-15.79236;-0.00000;,
 10.33410;-15.79236;10.33410;,
 0.00000;-15.79236;14.61470;,
 -10.33410;-15.79236;10.33410;,
 -14.61470;-15.79236;0.00000;,
 -10.33410;-15.79236;-10.33410;,
 0.00000;-15.79236;-14.61470;,
 0.00000;-18.69936;-0.00000;,
 0.00000;-18.69936;-0.00000;,
 0.00000;-18.69936;-0.00000;,
 0.00000;-18.69936;-0.00000;,
 0.00000;-18.69936;-0.00000;,
 0.00000;-18.69936;-0.00000;,
 0.00000;-18.69936;-0.00000;,
 0.00000;-18.69936;-0.00000;,
 -16.38840;46.72314;4.49474;,
 -0.03692;40.60959;-0.00000;,
 -14.94575;47.24099;4.11940;,
 -0.03692;40.60959;-0.00000;,
 -14.34820;48.83923;0.00000;,
 -0.03692;40.60959;-0.00000;,
 -14.94575;47.24099;-4.11940;,
 -0.03692;40.60959;-0.00000;,
 -16.38840;46.72314;-4.51312;,
 -0.03692;40.60959;-0.00000;,
 -16.28234;46.04737;-4.11940;,
 -0.03692;40.60959;-0.00000;,
 -16.87989;44.44912;0.00000;,
 -0.03692;40.60959;-0.00000;,
 -17.83100;46.04737;4.11940;,
 -0.03692;40.60959;-0.00000;,
 -16.38840;46.72314;4.49474;,
 -16.38840;46.72314;0.00000;,
 -16.38840;46.72314;4.49474;,
 -14.94575;47.24099;4.11940;,
 -14.34820;48.83923;0.00000;,
 -14.94575;47.24099;-4.11940;,
 -16.38840;46.72314;-4.51312;,
 -16.28234;46.04737;-4.11940;,
 -16.87989;44.44912;0.00000;,
 -17.83100;46.04737;4.11940;,
 16.59535;46.72314;-4.51312;,
 0.24387;40.60959;-0.01837;,
 15.15270;47.24099;-4.13778;,
 0.24387;40.60959;-0.01837;,
 14.55515;48.83923;-0.01838;,
 0.24387;40.60959;-0.01837;,
 15.15271;47.24099;4.10102;,
 0.24387;40.60959;-0.01837;,
 16.59535;46.72314;4.49474;,
 0.24387;40.60959;-0.01837;,
 16.48929;46.04737;4.10102;,
 0.24387;40.60959;-0.01837;,
 17.08684;44.44912;-0.01838;,
 0.24387;40.60959;-0.01837;,
 18.03795;46.04737;-4.13778;,
 0.24387;40.60959;-0.01837;,
 16.59535;46.72314;-4.51312;,
 16.59535;46.72314;-0.01838;,
 16.59535;46.72314;-4.51312;,
 15.15270;47.24099;-4.13778;,
 14.55515;48.83923;-0.01838;,
 15.15271;47.24099;4.10102;,
 16.59535;46.72314;4.49474;,
 16.48929;46.04737;4.10102;,
 17.08684;44.44912;-0.01838;,
 18.03795;46.04737;-4.13778;,
 4.85515;46.94761;16.61245;,
 0.36040;40.83406;0.26097;,
 4.47981;47.46545;15.16980;,
 0.36040;40.83406;0.26097;,
 0.36041;49.06369;14.57225;,
 0.36040;40.83406;0.26097;,
 -3.75900;47.46545;15.16981;,
 0.36040;40.83406;0.26097;,
 -4.15271;46.94761;16.61245;,
 0.36040;40.83406;0.26097;,
 -3.75900;46.27184;16.50639;,
 0.36040;40.83406;0.26097;,
 0.36041;44.67358;17.10394;,
 0.36040;40.83406;0.26097;,
 4.47981;46.27184;18.05505;,
 0.36040;40.83406;0.26097;,
 4.85515;46.94761;16.61245;,
 0.36041;46.94761;16.61245;,
 4.85515;46.94761;16.61245;,
 4.47981;47.46545;15.16980;,
 0.36041;49.06369;14.57225;,
 -3.75900;47.46545;15.16981;,
 -4.15271;46.94761;16.61245;,
 -3.75900;46.27184;16.50639;,
 0.36041;44.67358;17.10394;,
 4.47981;46.27184;18.05505;,
 -4.38089;46.74506;-16.08529;,
 0.11385;40.63152;0.26619;,
 -4.00555;47.26291;-14.64264;,
 0.11385;40.63152;0.26619;,
 0.11385;48.86115;-14.04508;,
 0.11385;40.63152;0.26619;,
 4.23325;47.26291;-14.64264;,
 0.11385;40.63152;0.26619;,
 4.62696;46.74506;-16.08529;,
 0.11385;40.63152;0.26619;,
 4.23325;46.06929;-15.97922;,
 0.11385;40.63152;0.26619;,
 0.11385;44.47104;-16.57678;,
 0.11385;40.63152;0.26619;,
 -4.00555;46.06929;-17.52789;,
 0.11385;40.63152;0.26619;,
 -4.38089;46.74506;-16.08529;,
 0.11385;46.74506;-16.08529;,
 -4.38089;46.74506;-16.08529;,
 -4.00555;47.26291;-14.64264;,
 0.11385;48.86115;-14.04508;,
 4.23325;47.26291;-14.64264;,
 4.62696;46.74506;-16.08529;,
 4.23325;46.06929;-15.97922;,
 0.11385;44.47104;-16.57678;,
 -4.00555;46.06929;-17.52789;;
 
 128;
 3;0,1,2;,
 3;3,4,1;,
 3;5,6,4;,
 3;7,8,6;,
 3;9,10,8;,
 3;11,12,10;,
 3;13,14,12;,
 3;15,16,14;,
 4;2,1,17,18;,
 4;1,4,19,17;,
 4;4,6,20,19;,
 4;6,8,21,20;,
 4;8,10,22,21;,
 4;10,12,23,22;,
 4;12,14,24,23;,
 4;14,16,25,24;,
 4;18,17,26,27;,
 4;17,19,28,26;,
 4;19,20,29,28;,
 4;20,21,30,29;,
 4;21,22,31,30;,
 4;22,23,32,31;,
 4;23,24,33,32;,
 4;24,25,34,33;,
 4;27,26,35,36;,
 4;26,28,37,35;,
 4;28,29,38,37;,
 4;29,30,39,38;,
 4;30,31,40,39;,
 4;31,32,41,40;,
 4;32,33,42,41;,
 4;33,34,43,42;,
 4;36,35,44,45;,
 4;35,37,46,44;,
 4;37,38,47,46;,
 4;38,39,48,47;,
 4;39,40,49,48;,
 4;40,41,50,49;,
 4;41,42,51,50;,
 4;42,43,52,51;,
 4;45,44,53,54;,
 4;44,46,55,53;,
 4;46,47,56,55;,
 4;47,48,57,56;,
 4;48,49,58,57;,
 4;49,50,59,58;,
 4;50,51,60,59;,
 4;51,52,61,60;,
 4;54,53,62,63;,
 4;53,55,64,62;,
 4;55,56,65,64;,
 4;56,57,66,65;,
 4;57,58,67,66;,
 4;58,59,68,67;,
 4;59,60,69,68;,
 4;60,61,70,69;,
 3;63,62,71;,
 3;62,64,72;,
 3;64,65,73;,
 3;65,66,74;,
 3;66,67,75;,
 3;67,68,76;,
 3;68,69,77;,
 3;69,70,78;,
 3;79,80,81;,
 3;81,82,83;,
 3;83,84,85;,
 3;85,86,87;,
 3;87,88,89;,
 3;89,90,91;,
 3;91,92,93;,
 3;93,94,95;,
 3;96,97,98;,
 3;96,98,99;,
 3;96,99,100;,
 3;96,100,101;,
 3;96,101,102;,
 3;96,102,103;,
 3;96,103,104;,
 3;96,104,97;,
 3;105,106,107;,
 3;107,108,109;,
 3;109,110,111;,
 3;111,112,113;,
 3;113,114,115;,
 3;115,116,117;,
 3;117,118,119;,
 3;119,120,121;,
 3;122,123,124;,
 3;122,124,125;,
 3;122,125,126;,
 3;122,126,127;,
 3;122,127,128;,
 3;122,128,129;,
 3;122,129,130;,
 3;122,130,123;,
 3;131,132,133;,
 3;133,134,135;,
 3;135,136,137;,
 3;137,138,139;,
 3;139,140,141;,
 3;141,142,143;,
 3;143,144,145;,
 3;145,146,147;,
 3;148,149,150;,
 3;148,150,151;,
 3;148,151,152;,
 3;148,152,153;,
 3;148,153,154;,
 3;148,154,155;,
 3;148,155,156;,
 3;148,156,149;,
 3;157,158,159;,
 3;159,160,161;,
 3;161,162,163;,
 3;163,164,165;,
 3;165,166,167;,
 3;167,168,169;,
 3;169,170,171;,
 3;171,172,173;,
 3;174,175,176;,
 3;174,176,177;,
 3;174,177,178;,
 3;174,178,179;,
 3;174,179,180;,
 3;174,180,181;,
 3;174,181,182;,
 3;174,182,175;;
 
 MeshMaterialList {
  2;
  128;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1;;
  Material {
   0.800000;0.000000;0.044000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.047200;0.599200;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  142;
  -0.000000;1.000000;0.000000;,
  0.000000;0.967256;-0.253803;,
  0.179466;0.967256;-0.179466;,
  0.253803;0.967256;0.000000;,
  0.179466;0.967256;0.179466;,
  0.000000;0.967256;0.253803;,
  -0.179466;0.967256;0.179466;,
  -0.253803;0.967256;0.000000;,
  -0.179466;0.967256;-0.179466;,
  0.000000;0.709230;-0.704977;,
  0.498494;0.709230;-0.498494;,
  0.704977;0.709230;0.000000;,
  0.498494;0.709230;0.498494;,
  0.000000;0.709230;0.704977;,
  -0.498494;0.709230;0.498494;,
  -0.704977;0.709230;0.000000;,
  -0.498494;0.709230;-0.498494;,
  0.000000;0.384551;-0.923104;,
  0.652733;0.384551;-0.652733;,
  0.923104;0.384551;0.000000;,
  0.652733;0.384551;0.652733;,
  0.000000;0.384551;0.923104;,
  -0.652733;0.384551;0.652733;,
  -0.923104;0.384551;0.000000;,
  -0.652733;0.384551;-0.652733;,
  0.000000;-0.185731;-0.982601;,
  0.694804;-0.185730;-0.694804;,
  0.982601;-0.185731;-0.000000;,
  0.694804;-0.185730;0.694804;,
  0.000000;-0.185731;0.982601;,
  -0.694804;-0.185730;0.694804;,
  -0.982601;-0.185731;0.000000;,
  -0.694804;-0.185730;-0.694804;,
  0.000000;-0.605116;-0.796138;,
  0.562954;-0.605115;-0.562954;,
  0.796138;-0.605116;-0.000000;,
  0.562954;-0.605115;0.562954;,
  0.000000;-0.605116;0.796138;,
  -0.562954;-0.605115;0.562954;,
  -0.796138;-0.605116;0.000000;,
  -0.562954;-0.605115;-0.562954;,
  0.000000;-0.757913;-0.652356;,
  0.461286;-0.757912;-0.461286;,
  0.652356;-0.757913;-0.000000;,
  0.461286;-0.757912;0.461286;,
  0.000000;-0.757913;0.652356;,
  -0.461286;-0.757912;0.461286;,
  -0.652356;-0.757913;0.000000;,
  -0.461286;-0.757912;-0.461286;,
  0.000000;-0.924735;-0.380610;,
  0.269133;-0.924735;-0.269133;,
  0.380610;-0.924735;-0.000000;,
  0.269133;-0.924735;0.269133;,
  0.000000;-0.924735;0.380610;,
  -0.269133;-0.924735;0.269133;,
  -0.380610;-0.924735;0.000000;,
  -0.269133;-0.924735;-0.269133;,
  0.000000;-1.000000;-0.000000;,
  0.151337;-0.289994;0.944987;,
  0.258257;-0.019385;0.965882;,
  0.498501;0.866889;-0.000000;,
  0.069111;0.974930;-0.211506;,
  0.165341;-0.260061;-0.951331;,
  -0.080917;-0.744105;-0.663144;,
  -0.222108;-0.974329;-0.036760;,
  -0.096002;-0.781327;0.616695;,
  -0.694951;0.716913;-0.055489;,
  -0.229515;0.950022;0.211615;,
  0.264642;-0.004070;-0.964338;,
  0.042965;-0.535214;-0.843623;,
  -0.211253;-0.926711;0.310772;,
  -0.381443;0.924393;0.000000;,
  -0.719897;0.694081;0.000000;,
  -0.710309;0.684837;-0.162664;,
  -0.337851;0.941199;0.000000;,
  -0.987907;-0.155049;0.000000;,
  -0.999134;0.028409;-0.030385;,
  -0.961796;0.207878;-0.178144;,
  -0.764379;0.623177;-0.165454;,
  -0.151337;-0.289995;-0.944987;,
  -0.258257;-0.019385;-0.965882;,
  -0.498501;0.866889;0.000000;,
  -0.069111;0.974930;0.211506;,
  -0.165341;-0.260061;0.951331;,
  0.080917;-0.744105;0.663144;,
  0.222108;-0.974329;0.036760;,
  0.096002;-0.781327;-0.616695;,
  0.694951;0.716913;0.055489;,
  0.229515;0.950022;-0.211615;,
  -0.264642;-0.004070;0.964338;,
  -0.042965;-0.535214;0.843623;,
  0.211253;-0.926711;-0.310771;,
  0.381443;0.924393;0.000000;,
  0.719897;0.694081;-0.000000;,
  0.710309;0.684837;0.162664;,
  0.337851;0.941199;-0.000000;,
  0.987906;-0.155054;-0.000001;,
  0.999135;0.028405;0.030384;,
  0.961796;0.207877;0.178144;,
  0.764379;0.623177;0.165454;,
  0.944987;-0.289995;-0.151336;,
  0.965882;-0.019386;-0.258256;,
  -0.000000;0.866889;-0.498501;,
  -0.211506;0.974930;-0.069112;,
  -0.951331;-0.260061;-0.165341;,
  -0.663145;-0.744105;0.080916;,
  -0.036760;-0.974329;0.222108;,
  0.616695;-0.781327;0.096002;,
  -0.055489;0.716913;0.694951;,
  0.211615;0.950022;0.229515;,
  -0.964338;-0.004071;-0.264642;,
  -0.843623;-0.535213;-0.042965;,
  0.310771;-0.926711;0.211253;,
  0.000000;0.924392;0.381443;,
  0.000000;0.694082;0.719896;,
  -0.162665;0.684837;0.710308;,
  0.000000;0.941200;0.337851;,
  0.000000;-0.155054;0.987906;,
  -0.030385;0.028404;0.999135;,
  -0.178144;0.207875;0.961797;,
  -0.165454;0.623176;0.764380;,
  -0.944987;-0.289995;0.151336;,
  -0.965882;-0.019386;0.258256;,
  0.000000;0.866889;0.498501;,
  0.211506;0.974930;0.069111;,
  0.951331;-0.260061;0.165341;,
  0.663144;-0.744105;-0.080916;,
  0.036760;-0.974329;-0.222108;,
  -0.616695;-0.781326;-0.096002;,
  0.055489;0.716912;-0.694951;,
  -0.211615;0.950022;-0.229515;,
  0.964338;-0.004070;0.264642;,
  0.843623;-0.535214;0.042965;,
  -0.310771;-0.926711;-0.211253;,
  0.000000;0.924393;-0.381443;,
  -0.000000;0.694081;-0.719897;,
  0.162665;0.684837;-0.710309;,
  0.000000;0.941199;-0.337851;,
  0.000000;-0.155054;-0.987906;,
  0.030385;0.028405;-0.999135;,
  0.178144;0.207876;-0.961796;,
  0.165454;0.623176;-0.764380;;
  128;
  3;0,2,1;,
  3;0,3,2;,
  3;0,4,3;,
  3;0,5,4;,
  3;0,6,5;,
  3;0,7,6;,
  3;0,8,7;,
  3;0,1,8;,
  4;1,2,10,9;,
  4;2,3,11,10;,
  4;3,4,12,11;,
  4;4,5,13,12;,
  4;5,6,14,13;,
  4;6,7,15,14;,
  4;7,8,16,15;,
  4;8,1,9,16;,
  4;9,10,18,17;,
  4;10,11,19,18;,
  4;11,12,20,19;,
  4;12,13,21,20;,
  4;13,14,22,21;,
  4;14,15,23,22;,
  4;15,16,24,23;,
  4;16,9,17,24;,
  4;17,18,26,25;,
  4;18,19,27,26;,
  4;19,20,28,27;,
  4;20,21,29,28;,
  4;21,22,30,29;,
  4;22,23,31,30;,
  4;23,24,32,31;,
  4;24,17,25,32;,
  4;25,26,34,33;,
  4;26,27,35,34;,
  4;27,28,36,35;,
  4;28,29,37,36;,
  4;29,30,38,37;,
  4;30,31,39,38;,
  4;31,32,40,39;,
  4;32,25,33,40;,
  4;33,34,42,41;,
  4;34,35,43,42;,
  4;35,36,44,43;,
  4;36,37,45,44;,
  4;37,38,46,45;,
  4;38,39,47,46;,
  4;39,40,48,47;,
  4;40,33,41,48;,
  4;41,42,50,49;,
  4;42,43,51,50;,
  4;43,44,52,51;,
  4;44,45,53,52;,
  4;45,46,54,53;,
  4;46,47,55,54;,
  4;47,48,56,55;,
  4;48,41,49,56;,
  3;49,50,57;,
  3;50,51,57;,
  3;51,52,57;,
  3;52,53,57;,
  3;53,54,57;,
  3;54,55,57;,
  3;55,56,57;,
  3;56,49,57;,
  3;58,58,59;,
  3;67,60,60;,
  3;60,60,61;,
  3;68,69,62;,
  3;62,69,63;,
  3;63,69,64;,
  3;64,70,65;,
  3;65,58,58;,
  3;66,71,67;,
  3;66,67,72;,
  3;66,72,73;,
  3;66,61,74;,
  3;75,75,76;,
  3;66,76,77;,
  3;66,77,78;,
  3;66,78,71;,
  3;79,79,80;,
  3;88,81,81;,
  3;81,81,82;,
  3;89,90,83;,
  3;83,90,84;,
  3;84,90,85;,
  3;85,91,86;,
  3;86,79,79;,
  3;87,92,88;,
  3;87,88,93;,
  3;87,93,94;,
  3;87,82,95;,
  3;96,96,97;,
  3;87,97,98;,
  3;87,98,99;,
  3;87,99,92;,
  3;100,100,101;,
  3;109,102,102;,
  3;102,102,103;,
  3;110,111,104;,
  3;104,111,105;,
  3;105,111,106;,
  3;106,112,107;,
  3;107,100,100;,
  3;108,113,109;,
  3;108,109,114;,
  3;108,114,115;,
  3;108,103,116;,
  3;117,117,118;,
  3;108,118,119;,
  3;108,119,120;,
  3;108,120,113;,
  3;121,121,122;,
  3;130,123,123;,
  3;123,123,124;,
  3;131,132,125;,
  3;125,132,126;,
  3;126,132,127;,
  3;127,133,128;,
  3;128,121,121;,
  3;129,134,130;,
  3;129,130,135;,
  3;129,135,136;,
  3;129,124,137;,
  3;138,138,139;,
  3;129,139,140;,
  3;129,140,141;,
  3;129,141,134;;
 }
 MeshTextureCoords {
  183;
  0.062500;0.000000;,
  0.125000;0.125000;,
  0.000000;0.125000;,
  0.187500;0.000000;,
  0.250000;0.125000;,
  0.312500;0.000000;,
  0.375000;0.125000;,
  0.437500;0.000000;,
  0.500000;0.125000;,
  0.562500;0.000000;,
  0.625000;0.125000;,
  0.687500;0.000000;,
  0.750000;0.125000;,
  0.812500;0.000000;,
  0.875000;0.125000;,
  0.937500;0.000000;,
  1.000000;0.125000;,
  0.125000;0.250000;,
  0.000000;0.250000;,
  0.250000;0.250000;,
  0.375000;0.250000;,
  0.500000;0.250000;,
  0.625000;0.250000;,
  0.750000;0.250000;,
  0.875000;0.250000;,
  1.000000;0.250000;,
  0.125000;0.375000;,
  0.000000;0.375000;,
  0.250000;0.375000;,
  0.375000;0.375000;,
  0.500000;0.375000;,
  0.625000;0.375000;,
  0.750000;0.375000;,
  0.875000;0.375000;,
  1.000000;0.375000;,
  0.125000;0.500000;,
  0.000000;0.500000;,
  0.250000;0.500000;,
  0.375000;0.500000;,
  0.500000;0.500000;,
  0.625000;0.500000;,
  0.750000;0.500000;,
  0.875000;0.500000;,
  1.000000;0.500000;,
  0.125000;0.625000;,
  0.000000;0.625000;,
  0.250000;0.625000;,
  0.375000;0.625000;,
  0.500000;0.625000;,
  0.625000;0.625000;,
  0.750000;0.625000;,
  0.875000;0.625000;,
  1.000000;0.625000;,
  0.125000;0.750000;,
  0.000000;0.750000;,
  0.250000;0.750000;,
  0.375000;0.750000;,
  0.500000;0.750000;,
  0.625000;0.750000;,
  0.750000;0.750000;,
  0.875000;0.750000;,
  1.000000;0.750000;,
  0.125000;0.875000;,
  0.000000;0.875000;,
  0.250000;0.875000;,
  0.375000;0.875000;,
  0.500000;0.875000;,
  0.625000;0.875000;,
  0.750000;0.875000;,
  0.875000;0.875000;,
  1.000000;0.875000;,
  0.062500;1.000000;,
  0.187500;1.000000;,
  0.312500;1.000000;,
  0.437500;1.000000;,
  0.562500;1.000000;,
  0.687500;1.000000;,
  0.812500;1.000000;,
  0.937500;1.000000;,
  0.000000;1.000000;,
  0.062500;0.000000;,
  0.125000;1.000000;,
  0.125000;0.000000;,
  0.250000;1.000000;,
  0.187500;0.000000;,
  0.375000;1.000000;,
  0.250000;0.000000;,
  0.500000;1.000000;,
  0.312500;0.000000;,
  0.625000;1.000000;,
  0.375000;0.000000;,
  0.750000;1.000000;,
  0.437500;0.000000;,
  0.875000;1.000000;,
  0.500000;0.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  0.062500;0.000000;,
  0.125000;1.000000;,
  0.125000;0.000000;,
  0.250000;1.000000;,
  0.187500;0.000000;,
  0.375000;1.000000;,
  0.250000;0.000000;,
  0.500000;1.000000;,
  0.312500;0.000000;,
  0.625000;1.000000;,
  0.375000;0.000000;,
  0.750000;1.000000;,
  0.437500;0.000000;,
  0.875000;1.000000;,
  0.500000;0.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  0.062500;0.000000;,
  0.125000;1.000000;,
  0.125000;0.000000;,
  0.250000;1.000000;,
  0.187500;0.000000;,
  0.375000;1.000000;,
  0.250000;0.000000;,
  0.500000;1.000000;,
  0.312500;0.000000;,
  0.625000;1.000000;,
  0.375000;0.000000;,
  0.750000;1.000000;,
  0.437500;0.000000;,
  0.875000;1.000000;,
  0.500000;0.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  0.062500;0.000000;,
  0.125000;1.000000;,
  0.125000;0.000000;,
  0.250000;1.000000;,
  0.187500;0.000000;,
  0.375000;1.000000;,
  0.250000;0.000000;,
  0.500000;1.000000;,
  0.312500;0.000000;,
  0.625000;1.000000;,
  0.375000;0.000000;,
  0.750000;1.000000;,
  0.437500;0.000000;,
  0.875000;1.000000;,
  0.500000;0.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;;
 }
}