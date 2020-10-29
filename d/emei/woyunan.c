inherit ROOM;

void create()
{
      set("short", "卧云庵");
        set("long", @LONG
卧云庵旁边有个井络泉，据说以前曾因饮水人多了而干涸，众尼
为之诵经，于是泉水复出。出了卧云庵便是睹光台，旁边便是华藏庵。
LONG );
        set("objects", ([
                CLASS_D("emei") + "/xuan" : 1,
        ]));
        set("outdoors", "emei");
        set("exits", ([
                "northeast" : __DIR__"jinding", 
                "southeast" : __DIR__"duguangtai", 
        ]));
        set("coor/x", -580);
        set("coor/y", -320);
        set("coor/z", 220);
        setup();
        replace_program(ROOM);
}