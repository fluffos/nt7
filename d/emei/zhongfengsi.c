inherit ROOM;

void create()
{
      set("short", "中峰寺");
        set("long", @LONG
中峰寺在白云峰下，始建于晋代，原为道观。传说观内的道人每
年在三月三日都献身给山中一条大蟒，以为可升仙。后来有个从资州
来的明果禅师，杀了那条大蟒，道士们始知上当，感激不已，自愿改
信佛教，从此改观为寺。这里往北可到清音阁，东下至神水庵。
LONG );
      set("objects", ([
               __DIR__+"npc/guest": 1,
      ]));
      set("exits", ([
          "west"     : __DIR__"qingyinge",
          "eastdown" : __DIR__"shenshuian",
      ]));
      set("outdoors", "emei");
        set("coor/x", -450);
        set("coor/y", -230);
        set("coor/z", 80);
        setup();
      replace_program(ROOM);
}