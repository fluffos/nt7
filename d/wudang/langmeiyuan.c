inherit ROOM;

void create()
{
        set("short", "榔梅园");
        set("long", @LONG
这里种满了榔梅树，花色深浅一如桃花，蒂垂丝作海棠状。榔和
梅本是山中的两种树，相传有一天玄武帝把梅枝插在榔干上，久而复
合，成此异种。据说榔梅果核不可带出武当山，违者必遭不昌。
LONG );
        set("objects", ([
                CLASS_D("wudang") + "/shouyuan": 1,
        ]));
        set("exits", ([
                "northup"  : __DIR__"taiziyan",
                "southup"  : __DIR__"wuyaling",
                "westup"   : __DIR__"nanyanfeng",
        ]));
        set("outdoors", "wudang");
        set("coor/x", -350);
        set("coor/y", -320);
        set("coor/z", 100);
        setup();
        replace_program(ROOM);
}