// This is a room made by wsl.
inherit ROOM;
void create()
{
    set("short", "大殿");
        set("long", @LONG
这一大片空间的高度并不是很高，可是在上面，星月夜空，由无
数小的油灯作为照明之用，看起来，真像是在旷野之中看夜空。而地
面上，有一道相当宽阔的河流，河水潺潺流过，但是在流的却是----
『水银』。
LONG );
    set("exits", ([
        "north" :__DIR__"dadian2",
]));
    setup();
    replace_program(ROOM);
}
