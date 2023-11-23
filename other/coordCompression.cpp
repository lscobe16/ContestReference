vz A; // zu komprimierende Werte
set<z> as(A.begin(), A.end());
vz ix2a(as.begin(), as.end());
map<z, z> a2ix;
for (z i = 0; i < ix2t.size(); i++) a2ix[ix2t[i]] = i;
@\opt{fe (a:A) a = a2ix[a];}@ // alle Vorkommen ersetzen
