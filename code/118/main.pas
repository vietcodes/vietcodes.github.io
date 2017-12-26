type int=longint;
var a,b,c,somax,somin: array[1..200000] of int;
    num: array[0..9] of int;
    n: int;
    ok: boolean;

procedure findmax();
var i: int;
begin
    for i:=1 to n do if a[i]>b[i] then begin
        somax:=a;
        exit();
    end else if a[i]<b[i] then begin
        somax:=b;
        exit();
    end;
    somax:=a;
end;
procedure findmin();
var i: int;
begin
    for i:=n downto 1 do if a[i]>b[i] then begin
        somin:=b;
        exit();
    end else if a[i]<b[i] then begin
        somin:=a;
        exit();
    end;
    somin:=a;
end;

function check(i: int): boolean;
var x: int;
begin
    if (c[i]<>-1) then begin
        if c[i]>b[i] then exit(false);
        if c[i]<b[i] then exit(true);
        exit(check(i-1));
    end;
    for x:=0 to b[i]-1 do if num[x]>0 then exit(true);
    if num[b[i]]=0 then exit(false);
    dec(num[b[i]]);
    check:=check(i-1);
    inc(num[b[i]]);
end;

procedure dq2(i: int);
var x: int;
begin
    if not check(n) then exit();
    if i>n then begin
        ok:=true;
        exit();
    end;
    for x:=0 to 9 do if num[x]>0 then begin
        dec(num[x]);
        c[i]:=x;
        dq2(i+1);
        if ok then exit();
        c[i]:=-1;
        inc(num[x]);
    end;
end;

procedure dq1(i: int);
var x: int;
begin
    if not check(n) then exit();
    if i>n then begin
        ok:=true;
        exit();
    end;
    for x:=a[i] to 9 do if num[x]>0 then begin
        c[i]:=x;
        dec(num[x]);
        if x>a[i] then dq2(i+1)
        else dq1(i+1);
        if ok then exit();
        c[i]:=-1;
        inc(num[x]);
    end;
end;

procedure main();
var i: int;
    t: char;
begin
    readln(n);
    for i:=1 to n do begin
        read(t);
        a[i]:=ord(t)-ord('0');
    end;
    readln();
    for i:=1 to n do begin
        read(t);
        b[i]:=ord(t)-ord('0');
    end;
    readln();
    fillchar(num,sizeof(num),0);
    for i:=1 to n do begin
        read(t);
        inc(num[ord(t)-ord('0')]);
    end;
    findmax();
    findmin();
    a:=somax;
    b:=somin;
    for i:=1 to n do c[i]:=-1;
    dq1(1);
    if ok then begin
        for i:=1 to n do write(c[i]);
    end else writeln(-1);
end;

begin
    main();
end.
