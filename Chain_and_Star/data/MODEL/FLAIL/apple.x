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
 173;
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
 24.94880;-8.38050;-24.94880;,
 0.00000;-8.38050;-35.28300;,
 35.28300;-8.38050;0.00000;,
 24.94880;-8.38050;24.94880;,
 -0.00000;-8.38050;35.28300;,
 -24.94880;-8.38050;24.94880;,
 -35.28300;-8.38050;0.00000;,
 -24.94880;-8.38050;-24.94880;,
 0.00000;-8.38050;-35.28300;,
 19.09500;-20.77020;-19.09500;,
 0.00000;-20.77020;-27.00440;,
 27.00440;-20.77020;0.00000;,
 19.09500;-20.77020;19.09500;,
 -0.00000;-20.77020;27.00440;,
 -19.09500;-20.77020;19.09500;,
 -27.00440;-20.77020;0.00000;,
 -19.09500;-20.77020;-19.09500;,
 0.00000;-20.77020;-27.00440;,
 10.33410;-29.04880;-10.33410;,
 0.00000;-29.04880;-14.61470;,
 14.61470;-29.04880;0.00000;,
 10.33410;-29.04880;10.33410;,
 -0.00000;-29.04880;14.61470;,
 -10.33410;-29.04880;10.33410;,
 -14.61470;-29.04880;0.00000;,
 -10.33410;-29.04880;-10.33410;,
 0.00000;-29.04880;-14.61470;,
 0.00000;-31.95580;-0.00000;,
 0.00000;-31.95580;-0.00000;,
 0.00000;-31.95580;-0.00000;,
 0.00000;-31.95580;-0.00000;,
 0.00000;-31.95580;-0.00000;,
 0.00000;-31.95580;-0.00000;,
 0.00000;-31.95580;-0.00000;,
 0.00000;-31.95580;-0.00000;,
 0.28498;59.38172;-3.96787;,
 3.09070;59.38172;-2.80571;,
 3.09070;36.11040;-2.80571;,
 0.28498;36.11040;-3.96787;,
 4.25286;59.38172;0.00000;,
 4.25286;36.11040;0.00000;,
 3.09070;59.38172;2.80571;,
 3.09070;36.11040;2.80571;,
 0.28496;59.38172;3.96787;,
 0.28496;36.11040;3.96787;,
 -2.52070;59.38172;2.80571;,
 -2.52070;36.11040;2.80571;,
 -3.68287;59.38172;-0.00000;,
 -3.68287;36.11040;-0.00000;,
 -2.52070;59.38172;-2.80571;,
 -2.52070;36.11040;-2.80571;,
 0.28498;59.38172;-3.96787;,
 0.28498;36.11040;-3.96787;,
 0.28498;59.38172;0.00000;,
 0.28498;59.38172;0.00000;,
 0.28498;59.38172;0.00000;,
 0.28498;59.38172;0.00000;,
 0.28498;59.38172;0.00000;,
 0.28498;59.38172;0.00000;,
 0.28498;59.38172;0.00000;,
 0.28498;59.38172;0.00000;,
 0.28498;36.11040;0.00000;,
 0.28498;36.11040;0.00000;,
 0.28498;36.11040;0.00000;,
 0.28498;36.11040;0.00000;,
 0.28498;36.11040;0.00000;,
 0.28498;36.11040;0.00000;,
 0.28498;36.11040;0.00000;,
 0.28498;36.11040;0.00000;,
 0.28498;59.38172;-3.96787;,
 3.09070;59.38172;-2.80571;,
 3.09070;36.11040;-2.80571;,
 0.28498;36.11040;-3.96787;,
 4.25286;59.38172;0.00000;,
 4.25286;36.11040;0.00000;,
 3.09070;59.38172;2.80571;,
 3.09070;36.11040;2.80571;,
 0.28496;59.38172;3.96787;,
 0.28496;36.11040;3.96787;,
 -2.52070;59.38172;2.80571;,
 -2.52070;36.11040;2.80571;,
 -3.68287;59.38172;-0.00000;,
 -3.68287;36.11040;-0.00000;,
 -2.52070;59.38172;-2.80571;,
 -2.52070;36.11040;-2.80571;,
 0.28498;59.38172;-3.96787;,
 0.28498;36.11040;-3.96787;,
 0.28498;59.38172;0.00000;,
 0.28498;59.38172;0.00000;,
 0.28498;59.38172;0.00000;,
 0.28498;59.38172;0.00000;,
 0.28498;59.38172;0.00000;,
 0.28498;59.38172;0.00000;,
 0.28498;59.38172;0.00000;,
 0.28498;59.38172;0.00000;,
 0.28498;36.11040;0.00000;,
 0.28498;36.11040;0.00000;,
 0.28498;36.11040;0.00000;,
 0.28498;36.11040;0.00000;,
 0.28498;36.11040;0.00000;,
 0.28498;36.11040;0.00000;,
 0.28498;36.11040;0.00000;,
 0.28498;36.11040;0.00000;,
 17.73584;55.06153;-5.82564;,
 0.27882;55.06153;0.00000;,
 17.73584;59.18091;-4.11936;,
 0.27882;55.06153;0.00000;,
 17.73584;60.88720;0.00000;,
 0.27882;55.06153;0.00000;,
 17.73584;59.18091;4.11936;,
 0.27882;55.06153;0.00000;,
 17.73584;55.06153;5.82564;,
 0.27882;55.06153;0.00000;,
 17.73584;50.94218;4.11935;,
 0.27882;55.06153;0.00000;,
 17.73584;49.23589;-0.00000;,
 0.27882;55.06153;0.00000;,
 17.73584;50.94218;-4.11935;,
 0.27882;55.06153;0.00000;,
 17.73584;55.06153;-5.82564;,
 17.73584;55.06153;0.00000;,
 17.73584;55.06153;-5.82564;,
 17.73584;59.18091;-4.11936;,
 17.73584;60.88720;0.00000;,
 17.73584;59.18091;4.11936;,
 17.73584;55.06153;5.82564;,
 17.73584;50.94218;4.11935;,
 17.73584;49.23589;-0.00000;,
 17.73584;50.94218;-4.11935;;
 
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
 4;79,80,81,82;,
 4;80,83,84,81;,
 4;83,85,86,84;,
 4;85,87,88,86;,
 4;87,89,90,88;,
 4;89,91,92,90;,
 4;91,93,94,92;,
 4;93,95,96,94;,
 3;97,80,79;,
 3;98,83,80;,
 3;99,85,83;,
 3;100,87,85;,
 3;101,89,87;,
 3;102,91,89;,
 3;103,93,91;,
 3;104,95,93;,
 3;105,82,81;,
 3;106,81,84;,
 3;107,84,86;,
 3;108,86,88;,
 3;109,88,90;,
 3;110,90,92;,
 3;111,92,94;,
 3;112,94,96;,
 4;113,114,115,116;,
 4;114,117,118,115;,
 4;117,119,120,118;,
 4;119,121,122,120;,
 4;121,123,124,122;,
 4;123,125,126,124;,
 4;125,127,128,126;,
 4;127,129,130,128;,
 3;131,114,113;,
 3;132,117,114;,
 3;133,119,117;,
 3;134,121,119;,
 3;135,123,121;,
 3;136,125,123;,
 3;137,127,125;,
 3;138,129,127;,
 3;139,116,115;,
 3;140,115,118;,
 3;141,118,120;,
 3;142,120,122;,
 3;143,122,124;,
 3;144,124,126;,
 3;145,126,128;,
 3;146,128,130;,
 3;147,148,149;,
 3;149,150,151;,
 3;151,152,153;,
 3;153,154,155;,
 3;155,156,157;,
 3;157,158,159;,
 3;159,160,161;,
 3;161,162,163;,
 3;164,165,166;,
 3;164,166,167;,
 3;164,167,168;,
 3;164,168,169;,
 3;164,169,170;,
 3;164,170,171;,
 3;164,171,172;,
 3;164,172,165;;
 
 MeshMaterialList {
  3;
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
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2;;
  Material {
   0.800000;0.000000;0.044000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.558400;0.388800;0.037600;1.000000;;
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
  77;
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
  0.000000;0.000000;-1.000000;,
  0.707107;0.000000;-0.707107;,
  1.000000;0.000000;0.000000;,
  0.707107;0.000000;0.707107;,
  0.000000;0.000000;1.000000;,
  -0.707107;0.000000;0.707107;,
  -1.000000;0.000000;0.000000;,
  -0.707107;0.000000;-0.707107;,
  0.000000;-0.384551;-0.923104;,
  0.652733;-0.384551;-0.652733;,
  0.923104;-0.384551;-0.000000;,
  0.652733;-0.384551;0.652733;,
  0.000000;-0.384551;0.923104;,
  -0.652733;-0.384551;0.652733;,
  -0.923104;-0.384551;0.000000;,
  -0.652733;-0.384551;-0.652733;,
  0.000000;-0.709230;-0.704977;,
  0.498494;-0.709230;-0.498494;,
  0.704977;-0.709230;-0.000000;,
  0.498494;-0.709230;0.498494;,
  0.000000;-0.709230;0.704977;,
  -0.498494;-0.709230;0.498494;,
  -0.704977;-0.709230;0.000000;,
  -0.498494;-0.709230;-0.498494;,
  0.000000;-0.924735;-0.380610;,
  0.269133;-0.924735;-0.269133;,
  0.380610;-0.924735;-0.000000;,
  0.269133;-0.924735;0.269133;,
  0.000000;-0.924735;0.380610;,
  -0.269133;-0.924735;0.269133;,
  -0.380610;-0.924735;0.000000;,
  -0.269133;-0.924735;-0.269133;,
  0.000000;-1.000000;-0.000000;,
  0.000000;1.000000;0.000000;,
  -0.000003;0.000000;-1.000000;,
  0.707107;0.000000;-0.707106;,
  1.000000;0.000000;0.000000;,
  0.707106;0.000000;0.707107;,
  -0.000005;0.000000;1.000000;,
  -0.707108;0.000000;0.707106;,
  -1.000000;0.000000;0.000000;,
  -0.707107;0.000000;-0.707106;,
  0.000000;-1.000000;-0.000000;,
  -0.316552;-0.000001;-0.948575;,
  -0.316553;0.670743;-0.670745;,
  -0.316553;0.948575;0.000000;,
  -0.316553;0.670743;0.670745;,
  -0.316552;-0.000001;0.948575;,
  -0.316553;-0.670743;0.670744;,
  -0.316553;-0.948575;0.000000;,
  -0.316553;-0.670743;-0.670744;,
  1.000000;0.000000;0.000000;;
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
  4;59,60,60,59;,
  4;60,61,61,60;,
  4;61,62,62,61;,
  4;62,63,63,62;,
  4;63,64,64,63;,
  4;64,65,65,64;,
  4;65,66,66,65;,
  4;66,59,59,66;,
  3;58,58,58;,
  3;58,58,58;,
  3;58,58,58;,
  3;58,58,58;,
  3;58,58,58;,
  3;58,58,58;,
  3;58,58,58;,
  3;58,58,58;,
  3;67,67,67;,
  3;67,67,67;,
  3;67,67,67;,
  3;67,67,67;,
  3;67,67,67;,
  3;67,67,67;,
  3;67,67,67;,
  3;67,67,67;,
  4;59,60,60,59;,
  4;60,61,61,60;,
  4;61,62,62,61;,
  4;62,63,63,62;,
  4;63,64,64,63;,
  4;64,65,65,64;,
  4;65,66,66,65;,
  4;66,59,59,66;,
  3;58,58,58;,
  3;58,58,58;,
  3;58,58,58;,
  3;58,58,58;,
  3;58,58,58;,
  3;58,58,58;,
  3;58,58,58;,
  3;58,58,58;,
  3;67,67,67;,
  3;67,67,67;,
  3;67,67,67;,
  3;67,67,67;,
  3;67,67,67;,
  3;67,67,67;,
  3;67,67,67;,
  3;67,67,67;,
  3;68,69,69;,
  3;69,69,70;,
  3;70,71,71;,
  3;71,71,72;,
  3;72,73,73;,
  3;73,73,74;,
  3;74,75,75;,
  3;75,75,68;,
  3;76,76,76;,
  3;76,76,76;,
  3;76,76,76;,
  3;76,76,76;,
  3;76,76,76;,
  3;76,76,76;,
  3;76,76,76;,
  3;76,76,76;;
 }
 MeshTextureCoords {
  173;
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
  0.000000;0.000000;,
  0.125000;0.000000;,
  0.125000;1.000000;,
  0.000000;1.000000;,
  0.250000;0.000000;,
  0.250000;1.000000;,
  0.375000;0.000000;,
  0.375000;1.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.625000;0.000000;,
  0.625000;1.000000;,
  0.750000;0.000000;,
  0.750000;1.000000;,
  0.875000;0.000000;,
  0.875000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.062500;0.000000;,
  0.187500;0.000000;,
  0.312500;0.000000;,
  0.437500;0.000000;,
  0.562500;0.000000;,
  0.687500;0.000000;,
  0.812500;0.000000;,
  0.937500;0.000000;,
  0.062500;1.000000;,
  0.187500;1.000000;,
  0.312500;1.000000;,
  0.437500;1.000000;,
  0.562500;1.000000;,
  0.687500;1.000000;,
  0.812500;1.000000;,
  0.937500;1.000000;,
  0.000000;0.000000;,
  0.125000;0.000000;,
  0.125000;1.000000;,
  0.000000;1.000000;,
  0.250000;0.000000;,
  0.250000;1.000000;,
  0.375000;0.000000;,
  0.375000;1.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.625000;0.000000;,
  0.625000;1.000000;,
  0.750000;0.000000;,
  0.750000;1.000000;,
  0.875000;0.000000;,
  0.875000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.062500;0.000000;,
  0.187500;0.000000;,
  0.312500;0.000000;,
  0.437500;0.000000;,
  0.562500;0.000000;,
  0.687500;0.000000;,
  0.812500;0.000000;,
  0.937500;0.000000;,
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
  0.000000;0.000000;;
 }
}