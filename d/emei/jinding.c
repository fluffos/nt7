inherit ROOM;

void create()
{
              set("short", "金顶");
        set("long", @LONG
这就是峨嵋山的主峰金顶。此峰耸立大地，高入云表，秀丽而又
壮美，李白赞颂它：『青冥倚天开，彩错疑画出』登上金顶，视野豁
然开朗，鸟看脚下，但见群峰涌绿叠翠，三江如丝如带；回首远眺，
则见大雪山横亘天际，贡嘎山直插苍穹。
LONG );
        set("no_sleep_room",1);
              set("outdoors", "emei");

              set("objects", ([
                   CLASS_D("emei") + "/fengling" : 1,
              ]));
              set("exits",([
                  "northdown" : __DIR__"wanxingan",
                  "southwest" : __DIR__"woyunan", 
                  "southeast" : __DIR__"huacangan",
              ]));

              set("no_clean_up", 0);
              set("coor/x", -570);
        set("coor/y", -310);
        set("coor/z", 220);
        setup();
}