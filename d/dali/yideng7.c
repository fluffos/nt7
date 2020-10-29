//Cracked by Kafei
// yideng quest room 7

inherit ROOM;

void create()
{
        set("short", "缺口");
        set("long", @LONG
山路中间突然中断，前面的山中间裂开，出现了一个缺口(gap)。
石壁直上直下，下面黑黝黝地深不见低，看来可能是地震造成的。山
路在对面的山上继续蜿蜒向前。
LONG );
        set("exits", ([
                "down":__DIR__"yideng5",
        ]));

        set("objects", ([
                CLASS_D("dali") + "/zhuziliu" : 1,
                ]) );

        set("item_desc",([
                "gap" : "这缺口看起来倒是不宽，可以跳过去，但是对面有个书生挡着，如果他在你跳到半空的时候出手攻击，那你是必死无疑。\n",
                ]));
        
        set("invalid_startroom", 1);
        set("no_clean_up", 0);
        set("coor/x", -38000);
        set("coor/y", -80000);
        set("coor/z", 300);
        setup();
}

void init()
{
        add_action("do_kill", "kill");
        add_action("do_kill", "fight");
        add_action("do_steal", "steal");
        add_action("do_steal", "throw");
}

int do_kill(string arg)
{
        if (arg=="zhu" || arg=="ziliu" || arg=="zhu ziliu") {
                tell_object(this_object(), "隔着这个缺口，你怎么攻击他啊？\n");
                return 1;
        }
        return 0;
}

int do_steal(string arg)
{
        tell_object(this_object(), "山顶之上，决无遮掩，你没有办法偷袭。\n");
        return 1;
}
