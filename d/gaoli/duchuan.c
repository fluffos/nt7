// /d/gaoli/xuanwumen
inherit ROOM;




void create()
{
        set("short", "渡船");
        set("long", @LONG
一叶小舟，最多也就能载七、八个人。一名六十多岁的老艄公手持
一根长竹篙，正在船尾吃力地撑着船。
LONG
        );
      set("no_fight",1);
        setup();
        replace_program(ROOM);
}



