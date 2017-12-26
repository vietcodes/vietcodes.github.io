type int=longint;
const di: array[1..4] of int=(-1,0,1,0);
dj: array[1..4] of int=(0,1,0,-1);
var m,n,i,j,i1,j1,k: int;
u,v: array[1..10000] of int;
p: array[1..100,1..100] of int;
c: array[1..100,1..100] of char;
first,last: int;

begin
    readln(m,n);
    for i:=1 to m do begin
        for j:=1 to n do read(c[i,j]);
        readln();
    end;
    first:=1;
    last:=1;
    for i:=1 to m do for j:=1 to n do begin
        p[i,j]:=0;
    end;
    for i:=1 to m do for j:=1 to n do if c[i,j]='C' then begin
        u[last]:=i;
        v[last]:=j;
        p[i,j]:=1;
        break;
    end;
    while first<=last do begin
        i:=u[first];
        j:=v[first];
        inc(first);
        for k:=1 to 4 do begin
            i1:=i+di[k];
            j1:=j+dj[k];
            if not((i1>=1)and(i1<=m)and(j1>=1)and(j1<=n)) then continue;
            if c[i1,j1]='*' then continue;
            if p[i1,j1]>0 then continue;
            inc(last);
            u[last]:=i1;
            v[last]:=j1;
            p[i1,j1]:=p[i,j]+1;
        end;
    end;
    for i:=1 to m do for j:=1 to n do if c[i,j]='B' then begin
        writeln(p[i,j]-1);
        break;
    end;
end.
