inherit ROOM;

void create ()
{
        set ("short", "山路");
        set("long", @LONG
这是一条黄土飞扬的山路，因为离嵩山等几处山脉还比较远，所
以它很是宽阔，路上来往人很多，路边相隔不远就有个小亭子供行人
歇脚，向南去不远就是开封城。由北而上直通嵩山，由此前住嵩山进
香、游玩的客人络绎不绝。
LONG );

          set("outdoors", "kaifeng");
          set("exits", ([
                  "eastdown" : __DIR__"jiaowai",
                  "westdown" : __DIR__"shanlu2",
        ]));

	set("coor/x", -5070);
	set("coor/y", 2270);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}