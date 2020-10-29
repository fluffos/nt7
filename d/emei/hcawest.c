inherit ROOM;

void create()
{
      set("short", "西侧殿");
        set("long", @LONG
这里是金顶华藏庵西侧殿，是接待香客及来宾的地方。殿内摆着
几张桌子，桌旁围放数把椅子。墙上悬着几幅字画，墙边一排书架，
架上摆满经书。几位进香客正在品茶养神，欣赏墙上的字画或翻阅架
上的经书。还有两个二十来岁的姑娘在向一位师太打听有关出家的事。
一个十来岁的小师太正在忙前忙后招待客人。南边有扇窗子(chuang)。
LONG );
              set("objects", ([
                   CLASS_D("emei") + "/wenqing" : 1,
              ]));
              set("item_desc", ([
                  "chuang" : "窗外可以看到峨眉山的秀丽山景。\n",
            ]));

        set("exits",([
                "east"   : __DIR__"hcazhengdian", 
              ]));
              set("coor/x", -570);
        set("coor/y", -320);
        set("coor/z", 220);
        setup();
}

void init()
{
        add_action("do_jump", "jump");
}

int do_jump(string arg)
{
        object me = this_player();

        if (! arg || arg != "chuang")
                return 0;

        message_vision("$N趁人不注意，跳出窗外。\n", me);
        me->move(__DIR__"xiaoshulin1");
        message_vision("$N从华藏庵里跳窗出来。\n", me);
        return 1;
}