#include <ansi.h>
inherit ROOM;

string look_pool();

void create()
{
      set("short", "洗象池");
        set("long", @LONG
洗象池原只是一亭，亭前有一个石砌的小池(pool)，池边不远就
是危岩。洗象池寓于一片冷杉林中，有若白云深处的仙山琼阁。若是
云收雾敛、碧空万里、月朗中天时，便觉万籁俱寂，清光无限，宛若
身在天宫，彻体生凉。这正是著名的「象池夜月」。由此向南上攀，
便至雷洞坪，东下至莲花石。
LONG );
      set("outdoors", "emei");
      set("exits", ([
          "eastdown"  : __DIR__"ztpo2",
          "southup"   : __DIR__"lingyunti",
      ]));
      set("item_desc", ([
          "pool" : (: look_pool :),
      ]));
        set("objects", ([ 
             __DIR__"npc/shenzy" : 1, 
        ])); 
      set("no_clean_up", 0);
        set("coor/x", -560);
        set("coor/y", -240);
        set("coor/z", 160);
        setup();
}

string look_pool()
{
    return WHT "\n这是一个石砌的六角小池，传说普贤乘象至"
           "此，必先在此池沐\n浴其象，而后才升至金顶，故"
           "为「洗象池」。\n" NOR;
}
