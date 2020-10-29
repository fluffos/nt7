// /d/gaoli/xuanwumen
// Room in 高丽
// rich 99/03/28
inherit ROOM;
void create()        
{
        set("short", "大堤");
        set("long", @LONG
这里是一个大堤。旁边就是汹涌的大海，阵阵大风吹来，海浪拍打
着堤岸，溅得你身上都是海水。放眼望去，大海一望无际，海的那边就
是战乱的中原了。
LONG
        );
set("outdoors", "gaoli");
set("exits", ([
                "north" : __DIR__"dadi2",
                "south":__DIR__"dadi4",
        ]));
       setup();
        
}
