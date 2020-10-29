// /d/gaoli/xingguan
// Room in 高丽
inherit ROOM;
void create()        
{
        set("short", "内堂");
        set("long", @LONG
这里是武士行馆的内堂，梁间有一块匾，上写着一个大大的「武」
字，堂上布置肃穆，两壁悬着长剑，腰刀。地下没有桌椅，地上放着几
个蒲团。
LONG);
set("exits", ([
                "out":__DIR__"xingguan"
        ]));
   set("objects",([
      __DIR__"obj/changjian":3,
      ]));
       setup();
        replace_program(ROOM);
}        
