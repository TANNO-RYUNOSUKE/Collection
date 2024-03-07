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
 99;
 -5.50048;0.00000;4.78881;,
 -8.88688;0.00000;3.38611;,
 -9.31198;1.45130;3.81121;,
 -5.50048;1.45130;5.38996;,
 8.97467;0.00000;3.38611;,
 5.58827;0.00000;4.78881;,
 5.58827;1.45130;5.38996;,
 9.39977;1.45130;3.81121;,
 10.37737;0.00000;-0.00034;,
 10.97852;1.45130;-0.00034;,
 8.97467;0.00000;-3.38674;,
 9.39977;1.45130;-3.81179;,
 5.58827;0.00000;-4.78939;,
 5.58827;1.45130;-5.39059;,
 -8.88688;0.00000;-3.38674;,
 -5.50048;0.00000;-4.78939;,
 -5.50048;1.45130;-5.39059;,
 -9.31198;1.45130;-3.81179;,
 -10.28958;0.00000;-0.00034;,
 -10.89073;1.45130;-0.00034;,
 -8.88688;0.00000;3.38611;,
 -9.31198;1.45130;3.81121;,
 -10.33823;2.05250;4.83741;,
 -5.50048;2.05250;6.84131;,
 5.58827;2.05250;6.84131;,
 10.42602;2.05250;4.83741;,
 12.42982;2.05250;-0.00034;,
 10.42602;2.05250;-4.83804;,
 5.58827;2.05250;-6.84189;,
 -5.50048;2.05250;-6.84189;,
 -10.33823;2.05250;-4.83804;,
 -12.34208;2.05250;-0.00034;,
 -10.33823;2.05250;4.83741;,
 -11.36448;1.45130;5.86366;,
 -5.50048;1.45130;8.29261;,
 5.58827;1.45130;8.29261;,
 11.45222;1.45130;5.86366;,
 13.88117;1.45130;-0.00034;,
 11.45222;1.45130;-5.86429;,
 5.58827;1.45130;-8.29324;,
 -5.50048;1.45130;-8.29324;,
 -11.36448;1.45130;-5.86429;,
 -13.79338;1.45130;-0.00034;,
 -11.36448;1.45130;5.86366;,
 -11.78953;0.00000;6.28871;,
 -5.50048;0.00000;8.89381;,
 5.58827;0.00000;8.89381;,
 11.87732;0.00000;6.28871;,
 14.48232;0.00000;-0.00034;,
 11.87732;0.00000;-6.28939;,
 5.58827;0.00000;-8.89439;,
 -5.50048;0.00000;-8.89439;,
 -11.78953;0.00000;-6.28939;,
 -14.39453;0.00000;-0.00034;,
 -11.78953;0.00000;6.28871;,
 -11.36448;-1.45130;5.86366;,
 -5.50048;-1.45130;8.29261;,
 5.58827;-1.45130;8.29261;,
 11.45222;-1.45130;5.86366;,
 13.88117;-1.45130;-0.00034;,
 11.45222;-1.45130;-5.86429;,
 5.58827;-1.45130;-8.29324;,
 -5.50048;-1.45130;-8.29324;,
 -11.36448;-1.45130;-5.86429;,
 -13.79338;-1.45130;-0.00034;,
 -11.36448;-1.45130;5.86366;,
 -10.33823;-2.05250;4.83741;,
 -5.50048;-2.05250;6.84131;,
 5.58827;-2.05250;6.84131;,
 10.42602;-2.05250;4.83741;,
 12.42982;-2.05250;-0.00034;,
 10.42602;-2.05250;-4.83804;,
 5.58827;-2.05250;-6.84189;,
 -5.50048;-2.05250;-6.84189;,
 -10.33823;-2.05250;-4.83804;,
 -12.34208;-2.05250;-0.00034;,
 -10.33823;-2.05250;4.83741;,
 -9.31198;-1.45130;3.81121;,
 -5.50048;-1.45130;5.38996;,
 5.58827;-1.45130;5.38996;,
 9.39977;-1.45130;3.81121;,
 10.97852;-1.45130;-0.00034;,
 9.39977;-1.45130;-3.81179;,
 5.58827;-1.45130;-5.39059;,
 -5.50048;-1.45130;-5.39059;,
 -9.31198;-1.45130;-3.81179;,
 -10.89073;-1.45130;-0.00034;,
 -9.31198;-1.45130;3.81121;,
 -8.88688;0.00000;3.38611;,
 -5.50048;0.00000;4.78881;,
 5.58827;0.00000;4.78881;,
 8.97467;0.00000;3.38611;,
 10.37737;0.00000;-0.00034;,
 8.97467;0.00000;-3.38674;,
 5.58827;0.00000;-4.78939;,
 -5.50048;0.00000;-4.78939;,
 -8.88688;0.00000;-3.38674;,
 -10.28958;0.00000;-0.00034;,
 -8.88688;0.00000;3.38611;;
 
 80;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,4,7,9;,
 4;10,8,9,11;,
 4;12,10,11,13;,
 4;14,15,16,17;,
 4;18,14,17,19;,
 4;20,18,19,21;,
 4;3,2,22,23;,
 4;7,6,24,25;,
 4;9,7,25,26;,
 4;11,9,26,27;,
 4;13,11,27,28;,
 4;17,16,29,30;,
 4;19,17,30,31;,
 4;21,19,31,32;,
 4;23,22,33,34;,
 4;25,24,35,36;,
 4;26,25,36,37;,
 4;27,26,37,38;,
 4;28,27,38,39;,
 4;30,29,40,41;,
 4;31,30,41,42;,
 4;32,31,42,43;,
 4;34,33,44,45;,
 4;36,35,46,47;,
 4;37,36,47,48;,
 4;38,37,48,49;,
 4;39,38,49,50;,
 4;41,40,51,52;,
 4;42,41,52,53;,
 4;43,42,53,54;,
 4;45,44,55,56;,
 4;47,46,57,58;,
 4;48,47,58,59;,
 4;49,48,59,60;,
 4;50,49,60,61;,
 4;52,51,62,63;,
 4;53,52,63,64;,
 4;54,53,64,65;,
 4;56,55,66,67;,
 4;58,57,68,69;,
 4;59,58,69,70;,
 4;60,59,70,71;,
 4;61,60,71,72;,
 4;63,62,73,74;,
 4;64,63,74,75;,
 4;65,64,75,76;,
 4;67,66,77,78;,
 4;69,68,79,80;,
 4;70,69,80,81;,
 4;71,70,81,82;,
 4;72,71,82,83;,
 4;74,73,84,85;,
 4;75,74,85,86;,
 4;76,75,86,87;,
 4;78,77,88,89;,
 4;80,79,90,91;,
 4;81,80,91,92;,
 4;82,81,92,93;,
 4;83,82,93,94;,
 4;85,84,95,96;,
 4;86,85,96,97;,
 4;87,86,97,98;,
 4;12,13,16,15;,
 4;13,28,29,16;,
 4;28,39,40,29;,
 4;39,50,51,40;,
 4;50,61,62,51;,
 4;61,72,73,62;,
 4;72,83,84,73;,
 4;83,94,95,84;,
 4;6,3,23,24;,
 4;6,5,0,3;,
 4;24,23,34,35;,
 4;90,79,78,89;,
 4;35,34,45,46;,
 4;79,68,67,78;,
 4;46,45,56,57;,
 4;68,57,56,67;;
 
 MeshMaterialList {
  1;
  80;
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
  0;;
  Material {
   0.400000;0.400000;0.400000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  80;
  -0.707109;0.000000;-0.707105;,
  -1.000000;-0.000000;0.000004;,
  -0.707106;0.000000;0.707108;,
  -0.196147;0.000000;0.980574;,
  -0.494183;0.715241;-0.494179;,
  -0.698881;0.715238;0.000002;,
  -0.494182;0.715240;0.494182;,
  -0.140450;0.704056;0.696117;,
  0.000000;1.000000;0.000001;,
  -0.000001;1.000000;0.000000;,
  -0.000000;1.000000;0.000000;,
  -0.000000;1.000000;0.000004;,
  0.494185;0.715239;0.494181;,
  0.698880;0.715239;-0.000000;,
  0.494182;0.715241;-0.494181;,
  0.140451;0.704053;-0.696119;,
  0.707110;0.000000;0.707103;,
  1.000000;0.000000;-0.000000;,
  0.707107;-0.000000;-0.707107;,
  0.196148;0.000000;-0.980574;,
  0.494185;-0.715239;0.494181;,
  0.698880;-0.715239;-0.000000;,
  0.494182;-0.715241;-0.494181;,
  0.140451;-0.704053;-0.696120;,
  0.000000;-1.000000;0.000001;,
  -0.000001;-1.000000;0.000000;,
  -0.000000;-1.000000;0.000000;,
  -0.000000;-1.000000;0.000004;,
  -0.494183;-0.715241;-0.494179;,
  -0.698881;-0.715238;0.000002;,
  -0.494182;-0.715240;0.494182;,
  -0.140450;-0.704056;0.696117;,
  0.707109;0.000000;-0.707105;,
  0.196146;0.000000;-0.980575;,
  0.494181;0.715242;-0.494179;,
  0.140450;0.704053;-0.696120;,
  0.196147;0.000000;0.980574;,
  0.707106;0.000000;0.707107;,
  0.140450;0.704056;0.696117;,
  0.494181;0.715241;0.494182;,
  1.000000;0.000000;0.000004;,
  0.698878;0.715241;0.000003;,
  -0.000001;1.000000;0.000001;,
  -0.000000;1.000000;0.000003;,
  0.000001;1.000000;0.000004;,
  -0.000001;1.000000;0.000001;,
  -0.000003;1.000000;0.000000;,
  -0.494187;0.715236;0.494182;,
  -0.140452;0.704055;0.696118;,
  -0.140450;0.704053;-0.696120;,
  -0.494184;0.715239;-0.494182;,
  -0.698885;0.715234;-0.000001;,
  -0.707111;0.000000;0.707102;,
  -0.196152;0.000000;0.980574;,
  -0.196147;0.000000;-0.980574;,
  -0.707108;0.000000;-0.707106;,
  -1.000000;0.000000;-0.000000;,
  -0.494187;-0.715236;0.494182;,
  -0.140452;-0.704055;0.696118;,
  -0.140450;-0.704053;-0.696120;,
  -0.494184;-0.715239;-0.494182;,
  -0.698885;-0.715234;-0.000001;,
  -0.000001;-1.000000;0.000001;,
  -0.000000;-1.000000;0.000003;,
  0.000001;-1.000000;0.000004;,
  -0.000001;-1.000000;0.000001;,
  -0.000003;-1.000000;0.000000;,
  0.494181;-0.715242;-0.494179;,
  0.140450;-0.704053;-0.696120;,
  0.140450;-0.704056;0.696117;,
  0.494181;-0.715241;0.494182;,
  0.698878;-0.715241;0.000003;,
  -0.140450;0.704053;-0.696120;,
  0.000001;1.000000;0.000004;,
  -0.196146;0.000000;-0.980575;,
  0.140453;0.704056;0.696117;,
  -0.140450;-0.704053;-0.696120;,
  0.196152;0.000000;0.980573;,
  0.000001;-1.000000;0.000004;,
  0.140453;-0.704056;0.696117;;
  80;
  4;33,32,34,35;,
  4;0,74,72,4;,
  4;1,0,4,5;,
  4;2,1,5,6;,
  4;3,2,6,7;,
  4;37,36,38,39;,
  4;40,37,39,41;,
  4;32,40,41,34;,
  4;35,34,42,43;,
  4;4,72,73,8;,
  4;5,4,8,9;,
  4;6,5,9,10;,
  4;7,6,10,11;,
  4;39,38,44,45;,
  4;41,39,45,46;,
  4;34,41,46,42;,
  4;43,42,47,48;,
  4;8,73,75,12;,
  4;9,8,12,13;,
  4;10,9,13,14;,
  4;11,10,14,15;,
  4;45,44,49,50;,
  4;46,45,50,51;,
  4;42,46,51,47;,
  4;48,47,52,53;,
  4;12,75,77,16;,
  4;13,12,16,17;,
  4;14,13,17,18;,
  4;15,14,18,19;,
  4;50,49,54,55;,
  4;51,50,55,56;,
  4;47,51,56,52;,
  4;53,52,57,58;,
  4;16,77,79,20;,
  4;17,16,20,21;,
  4;18,17,21,22;,
  4;19,18,22,23;,
  4;55,54,59,60;,
  4;56,55,60,61;,
  4;52,56,61,57;,
  4;58,57,62,63;,
  4;20,79,78,24;,
  4;21,20,24,25;,
  4;22,21,25,26;,
  4;23,22,26,27;,
  4;60,59,64,65;,
  4;61,60,65,66;,
  4;57,61,66,62;,
  4;63,62,67,68;,
  4;24,78,76,28;,
  4;25,24,28,29;,
  4;26,25,29,30;,
  4;27,26,30,31;,
  4;65,64,69,70;,
  4;66,65,70,71;,
  4;62,66,71,67;,
  4;68,67,32,33;,
  4;28,76,74,0;,
  4;29,28,0,1;,
  4;30,29,1,2;,
  4;31,30,2,3;,
  4;70,69,36,37;,
  4;71,70,37,40;,
  4;67,71,40,32;,
  4;3,7,38,36;,
  4;7,11,44,38;,
  4;11,15,49,44;,
  4;15,19,54,49;,
  4;19,23,59,54;,
  4;23,27,64,59;,
  4;27,31,69,64;,
  4;31,3,36,69;,
  4;72,35,43,73;,
  4;72,74,33,35;,
  4;73,43,48,75;,
  4;74,76,68,33;,
  4;75,48,53,77;,
  4;76,78,63,68;,
  4;77,53,58,79;,
  4;78,79,58,63;;
 }
 MeshTextureCoords {
  99;
  0.125000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.875000;,
  0.125000;0.875000;,
  0.250000;1.000000;,
  0.125000;1.000000;,
  0.125000;0.875000;,
  0.250000;0.875000;,
  0.375000;1.000000;,
  0.375000;0.875000;,
  0.500000;1.000000;,
  0.500000;0.875000;,
  0.625000;1.000000;,
  0.625000;0.875000;,
  0.750000;1.000000;,
  0.625000;1.000000;,
  0.625000;0.875000;,
  0.750000;0.875000;,
  0.875000;1.000000;,
  0.875000;0.875000;,
  1.000000;1.000000;,
  1.000000;0.875000;,
  0.000000;0.750000;,
  0.125000;0.750000;,
  0.125000;0.750000;,
  0.250000;0.750000;,
  0.375000;0.750000;,
  0.500000;0.750000;,
  0.625000;0.750000;,
  0.625000;0.750000;,
  0.750000;0.750000;,
  0.875000;0.750000;,
  1.000000;0.750000;,
  0.000000;0.625000;,
  0.125000;0.625000;,
  0.125000;0.625000;,
  0.250000;0.625000;,
  0.375000;0.625000;,
  0.500000;0.625000;,
  0.625000;0.625000;,
  0.625000;0.625000;,
  0.750000;0.625000;,
  0.875000;0.625000;,
  1.000000;0.625000;,
  0.000000;0.500000;,
  0.125000;0.500000;,
  0.125000;0.500000;,
  0.250000;0.500000;,
  0.375000;0.500000;,
  0.500000;0.500000;,
  0.625000;0.500000;,
  0.625000;0.500000;,
  0.750000;0.500000;,
  0.875000;0.500000;,
  1.000000;0.500000;,
  0.000000;0.375000;,
  0.125000;0.375000;,
  0.125000;0.375000;,
  0.250000;0.375000;,
  0.375000;0.375000;,
  0.500000;0.375000;,
  0.625000;0.375000;,
  0.625000;0.375000;,
  0.750000;0.375000;,
  0.875000;0.375000;,
  1.000000;0.375000;,
  0.000000;0.250000;,
  0.125000;0.250000;,
  0.125000;0.250000;,
  0.250000;0.250000;,
  0.375000;0.250000;,
  0.500000;0.250000;,
  0.625000;0.250000;,
  0.625000;0.250000;,
  0.750000;0.250000;,
  0.875000;0.250000;,
  1.000000;0.250000;,
  0.000000;0.125000;,
  0.125000;0.125000;,
  0.125000;0.125000;,
  0.250000;0.125000;,
  0.375000;0.125000;,
  0.500000;0.125000;,
  0.625000;0.125000;,
  0.625000;0.125000;,
  0.750000;0.125000;,
  0.875000;0.125000;,
  1.000000;0.125000;,
  0.000000;0.000000;,
  0.125000;0.000000;,
  0.125000;0.000000;,
  0.250000;0.000000;,
  0.375000;0.000000;,
  0.500000;0.000000;,
  0.625000;0.000000;,
  0.625000;0.000000;,
  0.750000;0.000000;,
  0.875000;0.000000;,
  1.000000;0.000000;;
 }
}