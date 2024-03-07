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
 221;
 0.70746;7.97808;6.16164;,
 -1.17912;4.62198;8.25690;,
 6.42348;1.39140;7.02342;,
 5.97798;4.27968;6.73344;,
 -7.91424;2.64294;-5.17206;,
 -8.50242;-1.66560;-2.92740;,
 -5.13384;-6.42264;1.50228;,
 -6.35172;-3.44934;4.48632;,
 -5.07342;6.52482;-6.07212;,
 1.49034;9.40008;-4.57284;,
 2.70834;6.42672;-7.55706;,
 -2.27682;0.10770;8.66292;,
 6.41934;-0.57030;6.93492;,
 3.36468;9.70116;2.25696;,
 7.78086;4.83678;4.47078;,
 0.91572;9.95376;-3.43440;,
 5.72400;8.59794;-2.04576;,
 -6.51042;0.90984;6.13578;,
 -2.11812;-4.25142;7.01346;,
 -2.78562;-7.53252;-2.78394;,
 -4.55946;-6.97620;0.36426;,
 -4.36080;2.72922;-8.47068;,
 2.86698;2.06754;-9.20658;,
 -2.05578;2.60706;-9.33960;,
 6.01836;-2.43942;6.48660;,
 5.97798;4.27968;6.73344;,
 9.14634;3.17670;8.04786;,
 10.39854;3.59778;6.09930;,
 7.78086;4.83678;4.47078;,
 -5.91132;-1.34820;-7.16736;,
 -0.12828;-5.80944;-6.68874;,
 -0.86652;-6.53922;-5.68374;,
 1.76934;-2.44674;-8.80050;,
 -0.90024;-7.22478;4.02942;,
 6.94194;5.62458;-5.02992;,
 8.92680;4.65312;1.86678;,
 9.54906;1.77720;1.90986;,
 4.92426;-4.98966;5.51154;,
 6.64464;-5.26062;3.13872;,
 9.48036;-5.07882;4.88340;,
 8.28576;-4.95582;6.90822;,
 4.92426;-4.98966;5.51154;,
 7.10064;1.26540;-6.67938;,
 1.44798;-8.33460;-0.25680;,
 9.59988;-0.17766;1.73130;,
 6.64464;-5.26062;3.13872;,
 59.92218;-16.29390;34.86786;,
 61.75878;-13.40952;36.20808;,
 60.51648;-13.55184;38.16150;,
 58.92276;-16.10412;36.97464;,
 4.10532;-6.61158;-4.16160;,
 6.00300;-3.24888;-6.27336;,
 9.14370;-2.05368;1.37304;,
 7.94556;-4.61790;0.56934;,
 8.50068;-3.04842;7.20522;,
 6.01836;-2.43942;6.48660;,
 4.92426;-4.98966;5.51154;,
 8.28576;-4.95582;6.90822;,
 7.94556;-4.61790;0.56934;,
 9.14370;-2.05368;1.37304;,
 10.95906;-2.74476;3.18324;,
 10.72206;-4.65498;2.92230;,
 -0.86898;10.50330;-0.27024;,
 -2.82126;9.49008;2.67882;,
 -5.41278;5.42412;5.72976;,
 -9.21498;2.13000;-0.52890;,
 -3.52620;8.78016;3.63450;,
 -8.62380;3.45450;1.93260;,
 -7.67022;6.20394;-1.82364;,
 11.41476;1.56222;3.78678;,
 9.54906;1.77720;1.90986;,
 8.92680;4.65312;1.86678;,
 11.58264;3.47766;4.06194;,
 61.10796;-7.96188;38.94480;,
 62.35032;-7.81944;36.99138;,
 61.18434;-4.36620;36.53934;,
 60.10698;-4.91244;38.54298;,
 5.97798;4.27968;6.73344;,
 6.42348;1.39140;7.02342;,
 8.95644;1.25856;7.80876;,
 9.14634;3.17670;8.04786;,
 6.41934;-0.57030;6.93492;,
 8.73498;-0.89598;7.50966;,
 61.26984;-10.84350;38.82630;,
 62.51328;-10.70136;36.87360;,
 11.19228;-0.59250;3.48942;,
 9.59988;-0.17766;1.73130;,
 8.01504;-6.11142;7.38204;,
 8.25468;-3.70962;7.74282;,
 9.51660;-6.26490;4.81770;,
 8.01504;-6.11142;7.38204;,
 11.36700;-3.32520;2.65098;,
 11.09442;-5.73114;2.34384;,
 12.18450;4.57032;3.78744;,
 11.94834;2.16888;3.42084;,
 9.10506;4.18992;8.82558;,
 10.67934;4.72332;6.35754;,
 8.83608;1.78446;8.51274;,
 9.10506;4.18992;8.82558;,
 8.54538;-0.96258;8.12778;,
 11.65764;-0.57816;3.03588;,
 36.74388;-7.77774;23.63334;,
 36.60450;-9.18438;23.42040;,
 36.37440;-9.97200;23.77806;,
 36.54792;-8.22078;24.04314;,
 36.60450;-9.18438;23.42040;,
 37.58880;-9.26136;21.74700;,
 37.60008;-10.06776;21.69432;,
 36.37440;-9.97200;23.77806;,
 38.61798;-8.93574;20.12616;,
 38.77884;-7.52646;20.30400;,
 39.08190;-7.90782;19.89738;,
 38.88162;-9.66240;19.67604;,
 39.11934;-4.30854;20.75496;,
 39.25644;-2.90220;20.97168;,
 39.67650;-2.15070;20.72862;,
 39.50580;-3.90162;20.45880;,
 38.26980;-2.82552;22.64886;,
 37.24296;-3.15084;24.26586;,
 37.16922;-2.46042;24.83064;,
 38.44788;-2.05536;22.81710;,
 37.24296;-3.15084;24.26586;,
 37.08438;-4.55988;24.08424;,
 36.97182;-4.21458;24.60456;,
 37.16922;-2.46042;24.83064;,
 36.91416;-6.16884;23.85882;,
 36.75990;-6.21768;24.32388;,
 38.94906;-5.91750;20.52948;,
 39.29388;-5.90472;20.17812;,
 40.04646;-11.88006;26.69142;,
 40.26978;-9.62622;27.03258;,
 41.62392;-12.00330;24.00954;,
 40.04646;-11.88006;26.69142;,
 43.53108;-9.22344;21.69696;,
 43.27332;-11.48160;21.41202;,
 44.29632;-1.81398;22.76676;,
 44.07672;-4.06740;22.41948;,
 41.06946;-2.21250;28.04610;,
 42.71514;-1.69122;25.45464;,
 40.81542;-4.47018;27.75516;,
 41.06946;-2.21250;28.04610;,
 40.54260;-7.04820;27.39384;,
 43.80384;-6.64542;22.05822;,
 40.76832;-10.70022;26.30640;,
 40.93872;-8.98290;26.56602;,
 41.94924;-10.79712;24.29730;,
 40.76832;-10.70022;26.30640;,
 43.38108;-8.68128;22.57014;,
 43.18494;-10.40184;22.35258;,
 43.96110;-3.06678;23.38050;,
 43.79352;-4.78380;23.11626;,
 41.54448;-3.36522;27.33426;,
 42.77742;-2.97018;25.39410;,
 41.35110;-5.08542;27.11220;,
 41.54448;-3.36522;27.33426;,
 41.14488;-7.03416;26.83914;,
 43.58730;-6.73248;22.84320;,
 47.57562;-14.30916;27.47124;,
 46.41918;-14.00148;29.51118;,
 46.41918;-14.00148;29.51118;,
 46.74612;-10.93044;29.96862;,
 47.04426;-8.15190;30.36048;,
 47.33430;-5.37180;30.74754;,
 47.65812;-2.29308;31.15188;,
 47.65812;-2.29308;31.15188;,
 48.91134;-1.68636;29.24010;,
 50.07474;-1.99452;27.19818;,
 49.77666;-5.07012;26.75172;,
 49.48662;-7.85022;26.36466;,
 49.18842;-10.62882;25.97274;,
 48.83580;-13.70298;25.55742;,
 -0.86898;10.50330;-0.27024;,
 3.36468;9.70116;2.25696;,
 7.78086;4.83678;4.47078;,
 11.58264;3.47766;4.06194;,
 8.92680;4.65312;1.86678;,
 12.18450;4.57032;3.78744;,
 39.25644;-2.90220;20.97168;,
 39.67650;-2.15070;20.72862;,
 44.29632;-1.81398;22.76676;,
 43.96110;-3.06678;23.38050;,
 50.07474;-1.99452;27.19818;,
 63.52452;-7.66332;34.99116;,
 62.50356;-4.61634;34.62210;,
 63.68634;-10.54506;34.87260;,
 62.93298;-13.25334;34.20780;,
 61.31928;-15.80814;33.05376;,
 43.18494;-10.40184;22.35258;,
 48.83580;-13.70298;25.55742;,
 43.27332;-11.48160;21.41202;,
 38.88162;-9.66240;19.67604;,
 38.61798;-8.93574;20.12616;,
 11.09442;-5.73114;2.34384;,
 10.72206;-4.65498;2.92230;,
 7.94556;-4.61790;0.56934;,
 61.14846;-10.82412;38.77950;,
 60.39864;-13.53294;38.11680;,
 60.51648;-13.55184;38.16150;,
 61.26984;-10.84350;38.82630;,
 60.99012;-7.94328;38.90016;,
 61.10796;-7.96188;38.94480;,
 59.88162;-4.49796;38.45664;,
 60.10698;-4.91244;38.54298;,
 60.90330;-3.83154;36.40794;,
 59.88162;-4.49796;38.45664;,
 62.29824;-4.19940;34.50294;,
 63.43242;-7.64154;34.90434;,
 62.29824;-4.19940;34.50294;,
 62.50356;-4.61634;34.62210;,
 63.52452;-7.66332;34.99116;,
 63.59076;-10.52244;34.78374;,
 63.68634;-10.54506;34.87260;,
 62.84100;-13.23132;34.12104;,
 62.93298;-13.25334;34.20780;,
 61.03620;-16.12554;32.83170;,
 61.31928;-15.80814;33.05376;,
 59.54130;-16.70310;34.60416;,
 61.03620;-16.12554;32.83170;,
 58.61964;-16.42398;36.78540;,
 58.61964;-16.42398;36.78540;,
 58.92276;-16.10412;36.97464;;
 
 164;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;4,8,9,10;,
 4;1,11,12,2;,
 4;13,0,3,14;,
 3;9,15,16;,
 4;17,7,18,11;,
 4;5,4,19,20;,
 3;21,22,23;,
 4;21,4,10,22;,
 4;11,18,24,12;,
 4;25,26,27,28;,
 3;29,30,31;,
 4;4,21,23,32;,
 4;29,4,32,30;,
 4;7,6,33,18;,
 4;10,9,16,34;,
 4;34,16,35,36;,
 4;18,33,37,24;,
 4;38,39,40,41;,
 3;32,23,22;,
 4;22,10,34,42;,
 4;20,19,43,33;,
 4;42,34,36,44;,
 4;33,43,45,37;,
 4;46,47,48,49;,
 3;31,30,50;,
 4;32,22,42,51;,
 4;51,42,44,52;,
 4;30,32,51,50;,
 4;50,51,52,53;,
 4;54,55,56,57;,
 4;58,59,60,61;,
 4;62,63,0,13;,
 4;64,17,11,1;,
 4;65,4,7,17;,
 3;8,15,9;,
 4;66,64,1,0;,
 3;64,67,17;,
 4;4,68,63,62;,
 4;4,65,67,64;,
 3;65,17,67;,
 4;68,4,64,66;,
 4;69,70,71,72;,
 4;73,74,75,76;,
 4;77,78,79,80;,
 4;79,78,81,82;,
 4;83,84,74,73;,
 4;85,86,70,69;,
 4;60,59,86,85;,
 4;48,47,84,83;,
 4;82,81,55,54;,
 4;54,57,87,88;,
 4;40,39,89,90;,
 4;61,60,91,92;,
 4;69,72,93,94;,
 4;27,26,95,96;,
 4;80,79,97,98;,
 4;79,82,99,97;,
 4;85,69,94,100;,
 4;60,85,100,91;,
 4;82,54,88,99;,
 4;101,102,103,104;,
 4;105,106,107,108;,
 4;109,110,111,112;,
 4;113,114,115,116;,
 4;117,118,119,120;,
 4;121,122,123,124;,
 4;122,125,126,123;,
 4;127,113,116,128;,
 4;110,127,128,111;,
 4;125,101,104,126;,
 4;104,103,129,130;,
 4;108,107,131,132;,
 4;112,111,133,134;,
 4;116,115,135,136;,
 4;120,119,137,138;,
 4;124,123,139,140;,
 4;123,126,141,139;,
 4;128,116,136,142;,
 4;111,128,142,133;,
 4;126,104,130,141;,
 4;130,129,143,144;,
 4;132,131,145,146;,
 4;134,133,147,148;,
 4;136,135,149,150;,
 4;138,137,151,152;,
 4;140,139,153,154;,
 4;139,141,155,153;,
 4;142,136,150,156;,
 4;133,142,156,147;,
 4;141,130,144,155;,
 4;90,89,106,105;,
 4;88,87,102,101;,
 4;99,88,101,125;,
 4;97,99,125,122;,
 4;98,97,122,121;,
 4;96,95,118,117;,
 4;94,93,114,113;,
 4;100,94,113,127;,
 4;91,100,127,110;,
 4;92,91,110,109;,
 4;146,145,157,158;,
 4;144,143,159,160;,
 4;155,144,160,161;,
 4;153,155,161,162;,
 4;154,153,162,163;,
 4;152,151,164,165;,
 4;150,149,166,167;,
 4;156,150,167,168;,
 4;147,156,168,169;,
 4;148,147,169,170;,
 3;63,68,66;,
 3;0,63,66;,
 3;6,20,33;,
 3;5,20,6;,
 4;15,8,4,171;,
 4;16,15,171,172;,
 4;35,16,172,173;,
 4;28,27,174,175;,
 4;176,174,27,96;,
 4;177,176,96,117;,
 4;178,177,117,120;,
 4;179,178,120,138;,
 4;180,179,138,152;,
 4;181,180,152,165;,
 4;182,183,75,74;,
 4;184,182,74,84;,
 4;185,184,84,47;,
 4;186,185,47,46;,
 4;145,187,188,157;,
 4;131,189,187,145;,
 4;107,190,189,131;,
 4;106,191,190,107;,
 4;89,192,191,106;,
 4;39,193,192,89;,
 4;194,193,39,38;,
 4;43,50,53,45;,
 4;19,31,50,43;,
 4;4,29,31,19;,
 4;195,196,197,198;,
 4;199,195,198,200;,
 4;201,199,200,202;,
 4;203,204,76,75;,
 4;183,205,203,75;,
 4;206,207,208,209;,
 4;210,206,209,211;,
 4;212,210,211,213;,
 4;214,212,213,215;,
 4;216,217,186,46;,
 4;218,216,46,49;,
 4;196,219,220,197;,
 4;160,159,219,196;,
 4;161,160,196,195;,
 4;162,161,195,199;,
 4;163,162,199,201;,
 4;165,164,204,203;,
 4;205,181,165,203;,
 4;167,166,207,206;,
 4;168,167,206,210;,
 4;169,168,210,212;,
 4;170,169,212,214;,
 4;157,188,217,216;,
 4;158,157,216,218;;
 
 MeshMaterialList {
  4;
  164;
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3;;
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "C:\\Users\\student\\Documents\\3d\\boss\\Robot_S_Mt_BaseColor.1002.png";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "C:\\Users\\student\\Documents\\3d\\boss\\Robot_S_Mt_BaseColor.1003.png";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "C:\\Users\\student\\Documents\\3d\\boss\\Robot_S_Mt_BaseColor.1004.png";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "C:\\Users\\student\\Documents\\3d\\boss\\Robot_S_Mt_BaseColor.1005.png";
   }
  }
 }
 MeshNormals {
  215;
  -0.105490;0.298679;0.948506;,
  -0.784934;-0.432399;0.443746;,
  -0.056891;-0.132648;0.989529;,
  -0.091714;-0.298893;0.949869;,
  -0.056155;0.047778;0.997278;,
  0.155527;0.551660;-0.819440;,
  0.104217;0.984935;0.137991;,
  0.819564;-0.187447;-0.541459;,
  0.429309;0.843161;0.323687;,
  0.855866;0.154829;-0.493478;,
  0.236284;-0.969026;0.071826;,
  0.031051;-0.312231;-0.949499;,
  -0.710569;0.473895;0.520110;,
  -0.966235;-0.244838;0.080277;,
  0.273113;0.932682;0.235613;,
  0.708934;0.067494;-0.702038;,
  -0.310834;-0.141764;0.939833;,
  0.645970;-0.681768;0.343389;,
  0.762662;-0.483464;0.429662;,
  0.770272;-0.482462;0.417027;,
  0.658661;-0.679941;0.322253;,
  0.832970;0.181149;0.522825;,
  0.825181;0.180182;0.535360;,
  0.748906;0.413271;0.518022;,
  -0.447199;-0.113329;0.887226;,
  -0.439588;-0.042829;0.897178;,
  0.459157;0.819586;0.342714;,
  0.523932;0.820897;0.227209;,
  0.613503;0.089833;-0.784566;,
  0.604334;0.002880;-0.796726;,
  0.271059;-0.958008;0.093529;,
  -0.095413;0.995293;0.016958;,
  -0.634934;-0.034495;0.771796;,
  -0.148090;0.983511;0.103801;,
  0.670306;-0.173804;0.721445;,
  -0.637465;-0.053185;0.768642;,
  0.815626;-0.332571;0.473445;,
  0.958086;-0.138714;0.250658;,
  0.902226;-0.239062;0.358940;,
  0.958533;-0.134434;0.251281;,
  0.852560;0.016475;0.522370;,
  0.670704;-0.170350;0.721899;,
  0.766515;-0.077616;0.637519;,
  -0.635036;-0.040905;0.771399;,
  0.958752;-0.136402;0.249378;,
  0.395388;0.086307;-0.914450;,
  0.669524;-0.172108;0.722576;,
  0.747448;-0.257728;0.612289;,
  -0.330286;-0.941399;-0.068397;,
  0.518312;0.054169;-0.853475;,
  -0.520355;-0.055812;0.852124;,
  0.520440;0.064247;-0.851478;,
  -0.520433;-0.064253;0.851482;,
  -0.004516;-0.996577;0.082549;,
  -0.853783;0.022039;-0.520163;,
  -0.943707;0.140359;-0.299527;,
  -0.943399;0.143216;-0.299144;,
  -0.894728;0.221633;-0.387738;,
  -0.824803;0.295947;-0.481783;,
  -0.707217;0.172736;-0.685570;,
  -0.707570;0.169187;-0.686091;,
  -0.783615;0.095921;-0.613797;,
  -0.243463;-0.944656;-0.219887;,
  -0.521274;-0.068310;0.850651;,
  -0.520398;-0.060033;0.851811;,
  -0.037939;0.997906;0.052388;,
  0.520484;0.074716;-0.850596;,
  0.520470;0.069482;-0.851048;,
  0.519382;0.059209;-0.852488;,
  0.766968;0.616766;-0.177085;,
  0.689359;0.085939;-0.719305;,
  0.395279;0.102150;-0.912863;,
  0.774663;0.416386;0.475942;,
  0.840576;0.182077;0.510176;,
  -0.445989;-0.077744;0.891656;,
  -0.434832;-0.023833;0.900196;,
  0.607001;0.046934;-0.793314;,
  0.603481;-0.021513;-0.797087;,
  0.199884;-0.958091;0.205202;,
  -0.080616;0.938158;-0.336691;,
  0.042662;0.735334;0.676361;,
  -0.503976;-0.443286;-0.741287;,
  -0.703730;-0.656885;0.270676;,
  0.014110;0.683820;-0.729514;,
  -0.917616;-0.387380;0.088980;,
  0.569842;0.799711;-0.189053;,
  -0.193228;-0.514565;0.835395;,
  -0.182618;-0.117463;0.976142;,
  -0.411181;-0.855513;-0.314686;,
  -0.521188;-0.849050;-0.086476;,
  0.161360;0.806828;-0.568324;,
  0.308196;0.678438;0.666887;,
  -0.261182;-0.818421;-0.511831;,
  -0.041347;-0.578512;-0.814626;,
  0.772065;0.405042;-0.489751;,
  0.067112;-0.997169;-0.033919;,
  0.141783;-0.881046;0.451283;,
  0.789301;0.002520;-0.614001;,
  0.166196;-0.985685;0.028352;,
  0.859805;-0.019476;-0.510251;,
  0.754884;-0.484361;0.442203;,
  0.632884;-0.683178;0.364316;,
  0.685923;-0.406984;-0.603219;,
  0.397481;-0.819425;-0.412979;,
  0.754528;-0.517324;-0.403811;,
  0.699796;-0.018219;-0.714110;,
  0.677276;-0.026943;-0.735236;,
  -0.379453;0.720299;-0.580676;,
  -0.926407;-0.325305;0.189596;,
  0.364868;0.885269;0.288392;,
  -0.545602;0.824425;-0.150471;,
  -0.070973;0.961350;-0.266025;,
  -0.810627;-0.116235;0.573910;,
  -0.216846;0.974429;-0.058869;,
  -0.903172;0.319920;0.286236;,
  -0.561631;0.688025;0.459558;,
  0.762017;0.414955;0.497134;,
  -0.306584;-0.050827;0.950486;,
  0.195495;0.915949;0.350455;,
  0.837843;-0.161716;0.521408;,
  0.856895;-0.159373;0.490235;,
  0.725010;0.019761;-0.688455;,
  0.847511;-0.160571;0.505906;,
  -0.956107;0.139832;-0.257500;,
  -0.853238;-0.000423;-0.521522;,
  -0.676058;0.174061;-0.715994;,
  -0.764310;0.088870;-0.638695;,
  -0.676512;0.169818;-0.716585;,
  -0.819618;0.317341;-0.476991;,
  -0.956638;0.134833;-0.258193;,
  -0.905764;0.227085;-0.357805;,
  -0.686425;0.171651;-0.706651;,
  -0.952367;0.138829;-0.271521;,
  -0.922417;0.069713;-0.379852;,
  -0.909645;0.080714;-0.407470;,
  -0.943928;0.141669;-0.298211;,
  -0.706356;0.171001;-0.686891;,
  -0.636264;-0.047045;0.770036;,
  -0.298145;-0.920767;-0.251590;,
  0.393697;0.078650;-0.915869;,
  0.391978;0.070980;-0.917232;,
  0.395345;0.094227;-0.913687;,
  -0.130346;-0.882814;0.451275;,
  -0.279242;-0.104223;0.954548;,
  -0.332957;0.928838;0.162479;,
  -0.747586;0.247020;-0.616519;,
  -0.768644;0.237552;-0.593932;,
  0.921371;-0.058071;0.384322;,
  -0.432855;0.642758;-0.632059;,
  0.332967;0.903108;-0.271163;,
  -0.568988;-0.568948;-0.593760;,
  -0.513075;-0.530949;-0.674424;,
  -0.451478;-0.487068;-0.747617;,
  -0.230314;-0.307551;-0.923238;,
  0.253903;-0.147719;-0.955883;,
  -0.339137;-0.149975;0.928705;,
  -0.597869;0.787498;-0.149666;,
  -0.926425;0.227041;0.300315;,
  -0.336670;-0.026631;0.941246;,
  -0.349756;-0.922493;-0.163334;,
  -0.634806;-0.028080;0.772161;,
  -0.102185;-0.994739;-0.007319;,
  -0.044828;-0.993747;-0.102257;,
  -0.493899;-0.075321;0.866251;,
  -0.494300;-0.081362;0.865475;,
  -0.493478;-0.069273;0.866995;,
  -0.492626;-0.063299;0.867936;,
  -0.491756;-0.057327;0.868844;,
  0.163080;0.971300;0.173152;,
  0.104441;0.958190;0.266390;,
  0.547888;0.066564;-0.833899;,
  0.548866;0.073968;-0.832632;,
  0.546879;0.059161;-0.835119;,
  0.546321;0.051659;-0.835982;,
  0.545731;0.044151;-0.836796;,
  -0.439344;-0.882860;-0.165934;,
  -0.368270;-0.882826;-0.291539;,
  -0.521743;-0.068948;0.850312;,
  -0.523039;-0.073632;0.849122;,
  -0.522106;-0.072364;0.849805;,
  -0.520431;-0.064253;0.851483;,
  -0.520713;-0.059243;0.851674;,
  -0.520985;-0.054239;0.851841;,
  -0.170656;0.984881;-0.029763;,
  -0.243798;0.965343;0.093138;,
  -0.127910;0.971465;0.199736;,
  0.520073;0.070467;-0.851210;,
  0.519682;0.076687;-0.850911;,
  0.520441;0.064243;-0.851478;,
  0.518796;0.058413;-0.852900;,
  0.517133;0.052583;-0.854288;,
  0.345406;0.931234;0.116178;,
  0.219713;0.972459;0.077784;,
  -0.041738;0.996669;-0.070062;,
  0.053189;0.993905;-0.096559;,
  -0.093959;0.983897;-0.152045;,
  -0.289526;-0.864404;-0.411072;,
  -0.149215;-0.919103;-0.364671;,
  -0.243417;-0.909414;-0.337216;,
  0.013080;-0.980530;-0.195936;,
  0.137485;-0.979118;-0.149753;,
  -0.369600;-0.158015;0.915657;,
  -0.368228;-0.090672;0.925304;,
  -0.355148;-0.024444;0.934491;,
  -0.345325;0.009971;0.938430;,
  0.386333;0.803902;0.452205;,
  0.617718;0.113034;-0.778234;,
  0.704198;0.151503;-0.693651;,
  0.697974;0.109981;-0.707627;,
  0.686839;0.029077;-0.726227;,
  0.680645;-0.054338;-0.730595;,
  0.677750;-0.098434;-0.728674;,
  0.337482;-0.941124;-0.019787;,
  -0.446528;-0.132954;0.884836;,
  -0.367162;-0.193406;0.909828;;
  164;
  4;80,0,4,91;,
  4;13,84,82,1;,
  4;148,107,83,5;,
  4;0,87,2,4;,
  4;109,80,91,8;,
  3;149,111,85;,
  4;112,1,86,87;,
  4;150,151,88,89;,
  3;79,90,6;,
  4;79,148,5,90;,
  4;87,86,3,2;,
  4;91,118,14,8;,
  3;81,93,92;,
  4;151,152,153,11;,
  4;81,148,11,93;,
  4;1,82,142,86;,
  4;5,83,85,94;,
  4;94,85,69,9;,
  4;86,142,96,3;,
  4;10,95,53,96;,
  3;11,153,154;,
  4;90,5,94,97;,
  4;89,88,98,142;,
  4;97,94,9,99;,
  4;142,98,10,96;,
  4;17,18,100,101;,
  3;92,93,103;,
  4;11,154,97,102;,
  4;102,97,99,7;,
  4;93,11,102,103;,
  4;103,102,7,104;,
  4;16,3,155,155;,
  4;104,7,105,106;,
  4;113,144,80,109;,
  4;12,112,87,0;,
  4;108,13,1,112;,
  3;107,111,83;,
  4;115,12,0,80;,
  3;12,114,112;,
  4;148,110,144,113;,
  4;148,156,114,12;,
  3;108,112,114;,
  4;157,13,12,115;,
  4;15,9,69,70;,
  4;22,21,116,23;,
  4;158,4,117,158;,
  4;117,4,2,143;,
  4;119,122,21,22;,
  4;121,99,9,15;,
  4;105,7,99,121;,
  4;100,18,122,119;,
  4;143,2,3,16;,
  4;123,133,133,123;,
  4;133,124,124,133;,
  4;126,125,125,126;,
  4;127,145,145,127;,
  4;128,130,130,128;,
  4;130,129,129,130;,
  4;129,132,132,129;,
  4;131,127,127,131;,
  4;125,131,131,125;,
  4;132,123,123,132;,
  4;55,134,134,55;,
  4;134,54,54,134;,
  4;61,60,60,61;,
  4;59,146,146,59;,
  4;58,57,57,58;,
  4;57,56,56,57;,
  4;56,135,135,56;,
  4;136,59,59,136;,
  4;60,136,136,60;,
  4;135,55,55,135;,
  4;137,35,35,137;,
  4;159,138,138,159;,
  4;140,139,139,140;,
  4;141,71,71,141;,
  4;31,33,33,31;,
  4;160,32,32,160;,
  4;32,43,43,32;,
  4;45,141,141,45;,
  4;139,45,45,139;,
  4;43,137,137,43;,
  4;34,47,47,34;,
  4;47,36,36,47;,
  4;38,37,37,38;,
  4;39,147,147,39;,
  4;40,42,42,40;,
  4;42,41,41,42;,
  4;41,46,46,41;,
  4;44,39,39,44;,
  4;37,44,44,37;,
  4;46,34,34,46;,
  4;161,162,162,161;,
  4;163,164,164,163;,
  4;165,163,163,165;,
  4;166,165,165,166;,
  4;167,166,166,167;,
  4;168,169,169,168;,
  4;170,171,171,170;,
  4;172,170,170,172;,
  4;173,172,172,173;,
  4;174,173,173,174;,
  4;175,176,62,48;,
  4;177,178,179,63;,
  4;180,177,63,52;,
  4;181,180,52,64;,
  4;182,181,64,50;,
  4;183,184,185,65;,
  4;186,187,66,67;,
  4;188,186,67,51;,
  4;189,188,51,68;,
  4;190,189,68,49;,
  3;144,110,115;,
  3;80,144,115;,
  3;82,89,142;,
  3;84,89,82;,
  4;111,107,148,113;,
  4;85,111,113,109;,
  4;69,85,109,8;,
  4;8,14,191,69;,
  4;145,145,128,128;,
  4;192,192,168,168;,
  4;146,146,58,58;,
  4;193,193,31,31;,
  4;147,147,40,40;,
  4;194,195,183,65;,
  4;73,72,116,21;,
  4;120,73,21,122;,
  4;19,120,122,18;,
  4;20,19,18,17;,
  4;176,196,197,62;,
  4;36,38,38,36;,
  4;138,198,198,138;,
  4;54,61,61,54;,
  4;162,199,199,162;,
  4;124,126,126,124;,
  4;200,200,95,10;,
  4;98,103,104,10;,
  4;88,92,103,98;,
  4;13,81,92,88;,
  4;74,24,201,202;,
  4;25,74,202,203;,
  4;75,25,203,204;,
  4;26,205,23,116;,
  4;72,27,26,116;,
  4;28,206,207,208;,
  4;76,28,208,209;,
  4;29,76,209,210;,
  4;77,29,210,211;,
  4;30,212,20,17;,
  4;78,30,17,101;,
  4;24,213,214,201;,
  4;63,179,213,24;,
  4;52,63,24,74;,
  4;64,52,74,25;,
  4;50,64,25,75;,
  4;65,185,205,26;,
  4;27,194,65,26;,
  4;67,66,206,28;,
  4;51,67,28,76;,
  4;68,51,76,29;,
  4;49,68,29,77;,
  4;62,197,212,30;,
  4;48,62,30,78;;
 }
 MeshTextureCoords {
  221;
  4.055050;0.881520;,
  4.060270;0.884910;,
  4.058170;0.899080;,
  4.053180;0.893370;,
  4.084350;0.868510;,
  4.080890;0.875840;,
  4.078470;0.886290;,
  4.073570;0.884460;,
  4.096790;0.867090;,
  4.108950;0.873870;,
  4.104710;0.877930;,
  4.065800;0.888310;,
  4.062360;0.901430;,
  4.048350;0.877970;,
  4.047710;0.892750;,
  4.110260;0.872450;,
  4.113620;0.881510;,
  4.068610;0.881590;,
  4.071560;0.891260;,
  4.084300;0.887050;,
  4.080060;0.886640;,
  4.093280;0.872650;,
  4.100030;0.881580;,
  4.095960;0.875400;,
  4.066990;0.902720;,
  4.526970;0.871170;,
  4.527250;0.865740;,
  4.531540;0.865740;,
  4.531640;0.870830;,
  4.087750;0.875830;,
  4.090150;0.886280;,
  4.088490;0.886640;,
  4.095060;0.884450;,
  4.077340;0.893250;,
  4.108390;0.884890;,
  4.115300;0.893380;,
  4.110500;0.899050;,
  4.074600;0.902230;,
  4.531650;0.642380;,
  4.531650;0.647480;,
  4.527360;0.647440;,
  4.526890;0.642020;,
  4.102860;0.888270;,
  4.084310;0.894100;,
  4.106350;0.901390;,
  4.084380;0.904360;,
  4.532600;0.746540;,
  4.532650;0.752150;,
  4.529030;0.752100;,
  4.529040;0.747050;,
  4.091310;0.893240;,
  4.097100;0.891230;,
  4.101740;0.902680;,
  4.094120;0.902220;,
  4.897400;0.623440;,
  4.897040;0.619210;,
  4.901390;0.617970;,
  4.900390;0.623440;,
  4.842780;0.619800;,
  4.847130;0.621070;,
  4.846750;0.625290;,
  4.843750;0.625260;,
  4.054920;0.868260;,
  4.058460;0.872460;,
  4.063960;0.877930;,
  4.075390;0.872660;,
  4.059760;0.873880;,
  4.071070;0.873900;,
  4.071940;0.867110;,
  4.853460;0.625290;,
  4.853080;0.621070;,
  4.857420;0.619800;,
  4.856450;0.625270;,
  4.529010;0.761100;,
  4.532630;0.761060;,
  4.532580;0.766690;,
  4.529010;0.766160;,
  4.886730;0.617970;,
  4.891090;0.619180;,
  4.890680;0.623400;,
  4.887690;0.623360;,
  4.894060;0.619510;,
  4.894040;0.623410;,
  4.529040;0.756600;,
  4.532650;0.756610;,
  4.850100;0.625280;,
  4.850100;0.621380;,
  4.902060;0.624510;,
  4.898310;0.624490;,
  4.531650;0.649280;,
  4.526900;0.649470;,
  4.845820;0.626330;,
  4.842080;0.626340;,
  4.858130;0.626340;,
  4.854380;0.626340;,
  4.526800;0.863700;,
  4.531550;0.863930;,
  4.889760;0.624440;,
  4.886010;0.624420;,
  4.894030;0.624450;,
  4.850100;0.626320;,
  4.896260;0.674940;,
  4.898460;0.674940;,
  4.899590;0.675740;,
  4.896870;0.675730;,
  4.528350;0.700030;,
  4.531650;0.699980;,
  4.531660;0.701240;,
  4.528000;0.701270;,
  4.845380;0.676790;,
  4.847580;0.676800;,
  4.846960;0.677590;,
  4.844240;0.677580;,
  4.852600;0.676800;,
  4.854800;0.676790;,
  4.855930;0.677580;,
  4.853210;0.677590;,
  4.531980;0.813230;,
  4.528690;0.813180;,
  4.528350;0.811960;,
  4.532000;0.811970;,
  4.889040;0.674890;,
  4.891240;0.674920;,
  4.890620;0.675700;,
  4.887900;0.675670;,
  4.893750;0.674930;,
  4.893750;0.675710;,
  4.850090;0.676800;,
  4.850090;0.677590;,
  4.901240;0.684210;,
  4.897730;0.684190;,
  4.531880;0.710580;,
  4.527170;0.710660;,
  4.846070;0.686050;,
  4.842550;0.686060;,
  4.857630;0.686050;,
  4.854120;0.686050;,
  4.527360;0.802660;,
  4.532100;0.802630;,
  4.889680;0.684150;,
  4.886170;0.684140;,
  4.893700;0.684180;,
  4.850090;0.686050;,
  4.899430;0.685530;,
  4.896740;0.685510;,
  4.531940;0.712580;,
  4.527840;0.712690;,
  4.847050;0.687370;,
  4.844360;0.687390;,
  4.855830;0.687380;,
  4.853140;0.687360;,
  4.528000;0.800600;,
  4.532120;0.800630;,
  4.890660;0.685480;,
  4.887970;0.685480;,
  4.893700;0.685490;,
  4.850090;0.687370;,
  4.532190;0.723850;,
  4.528080;0.723840;,
  4.902780;0.696200;,
  4.897980;0.696200;,
  4.893650;0.696190;,
  4.889320;0.696160;,
  4.884520;0.696120;,
  4.528160;0.789390;,
  4.532270;0.789370;,
  4.859230;0.698030;,
  4.854440;0.698050;,
  4.850100;0.698060;,
  4.845770;0.698060;,
  4.840970;0.698040;,
  4.113830;0.868280;,
  4.120340;0.877990;,
  4.120720;0.892590;,
  4.535810;0.865820;,
  4.536240;0.871250;,
  4.536310;0.863790;,
  4.535280;0.813240;,
  4.535650;0.812030;,
  4.536840;0.802770;,
  4.536230;0.800700;,
  4.536370;0.789500;,
  4.536240;0.761140;,
  4.536150;0.766240;,
  4.536260;0.756610;,
  4.536270;0.752080;,
  4.536170;0.746960;,
  4.536050;0.712460;,
  4.536280;0.723690;,
  4.536620;0.710390;,
  4.535310;0.701210;,
  4.534950;0.700000;,
  4.536400;0.649470;,
  4.535930;0.647440;,
  4.536410;0.642020;,
  4.893530;0.721750;,
  4.897890;0.720950;,
  4.897890;0.721140;,
  4.893530;0.721950;,
  4.889180;0.720910;,
  4.889170;0.721100;,
  4.884250;0.718250;,
  4.884820;0.718720;,
  4.532570;0.767650;,
  4.528910;0.766930;,
  4.536240;0.767020;,
  4.854480;0.722800;,
  4.859420;0.720160;,
  4.858850;0.720630;,
  4.854480;0.723000;,
  4.850120;0.723630;,
  4.850120;0.723830;,
  4.845770;0.722810;,
  4.845770;0.723000;,
  4.840830;0.720180;,
  4.841390;0.720650;,
  4.532580;0.745580;,
  4.536260;0.746180;,
  4.528940;0.746280;,
  4.902840;0.718340;,
  4.902270;0.718800;;
 }
}
