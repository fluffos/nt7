// Room: /d/guiyun/zhongting.c
// Last Modified by Lonely on Jul. 9 2001

#include <ansi.h>
inherit ROOM;

string look_xiao();
string look_zishi();

void create()
{
        set("short","中厅");
        set("long",@LONG
这是归云庄的中厅。庄中的大事以及召集弟子训话都是在这里进行
的。由于修建年代久远，看起来已颇为陈旧，但打扫得十分干净，光线
也较为充足，完全没有陈年旧宅的阴晦之气。四壁挂着一些古人书画精
品，皆为上乘之作，显得主人眼光不凡，胸中大有丘壑。
    靠里面是一张太师椅，椅后的墙上挂着一幅画(hua)。
LONG );
        set("objects",([
                __DIR__"npc/kezhene" : 1,
                __DIR__"npc/zhucong" : 1,
                __DIR__"npc/hanbaoju" : 1,
                __DIR__"npc/nanxiren" : 1,
                __DIR__"npc/zhangasheng" : 1,
                __DIR__"npc/quanjinfa" : 1,
                __DIR__"npc/hanxiaoying" : 1,
                __DIR__"npc/guanjia" :     1,
                __DIR__"npc/zhuangding3" : 1,
        ]));
        set("exits",([
                "east"  : __DIR__"qianting",
                "north" : __DIR__"zoulang1",
                "south" : __DIR__"zoulang4",
        ]) );
        set("item_desc", ([
                "hua" :  "画中是一位形貌清矍的青衫老者，正在吹箫(xiao)，但是他的姿势(zishi)却有点奇怪。\n",
                "xiao" : (: look_xiao :),
                "zishi" : (: look_zishi :),
        ]) );

        set("no_clean_up",0);
        set("coor/x", 260);
        set("coor/y", -830);
        set("coor/z", 0);
        setup();
}

string look_xiao()
{
        object me = this_player();

        if( !query_temp("guiyun_hua", me))return "画中老人拿箫的姿势甚是怪异！\n";
        set_temp("guiyun_hua", 2, me);
        return "原来画中老人竟是把手中握着的箫当作了剑来舞。\n";
}

string look_zishi()
{
        object me = this_player();
        int level, exp;

        level = me->query_skill("sword", 1);
        exp=query("combat_exp", me);
        if( query_temp("guiyun_hua", me)<2 )
        {
                set_temp("guiyun_hua", 1, me);
                return "你仔细地端详着画中老人的身姿，恍惚间仿佛看见老人正在缓缓舞动着什么。\n";
        }
        else
        {
                write("原来画中老人舞箫的姿势里竟然暗藏着高深的剑法！\n");
                if (me->is_busy())
                {
                        write("可惜你现在正忙着做别的事，无法专心研究这幅画。\n");
                        return "";
                }
                if( me->is_fighting() ) {
                        write("可惜你现在正在战斗中，无法专心研究这幅画。\n");
                        return "";
                }
                if( query("jing", me)<30 )
                        return "可惜你太累了，无法集中精神来研究这幅画。\n";
                if (me->query_skill("sword", 1) > 100)
                        return "这幅在以前的你看来很艰深的画对现在的你而言已经没有什么可值得研究的了。\n";
                if ((int)me->query_skill("sword", 1) < 30 )
                        return "你努力试图从画中老人的身姿里看出些什么，却发现一切都是徒劳的。\n";

                me->receive_damage("jing", 25);
                if( level * level * level /10 < exp)
                        me->improve_skill("sword",query("int", me));

                write("你仔细端详着画中老人舞箫的身姿。\n");
                if (!random(8))
                        tell_room(this_object(), me->name() + "仔细端详着画中老人舞箫的身姿。\n", ({me}));
                return "你对剑法运用的微妙之处有了进一步的认识。\n";
        }
}

void init()
{
        object me = this_player();
        int score, skill, age;

        if( query("age", me) >= 30 || random(query("kar", me))<15 )
                return;

        if( query("family/master_id", me) != "lu chengfeng" && 
            query("family/master_id", me) != "qu lingfeng" )
                return;


        age=query("age", me)-10;
        skill = (me->query_skill("force") + me->query_skill("dodge") +
                me->query_skill("strike") + me->query_skill("qimen-wuxing")) / 4;
        skill*=query("combat_exp", me)/1000;
        score = skill / age;

        if (score < 1000)
                return;

        remove_call_out("recruit_ob");
        call_out("recruit_ob", 1, me);

        tell_object(me, CYN "你觉得身后有点古怪，似乎有人跟随？\n" NOR);
}

void recruit_ob(object me)
{
        object ob, *obj;
        int i, j = 0;

        if (! me) return;

        obj = all_inventory(environment(me));

        for(i = 0; i < sizeof(obj); i++)
        {
                if (playerp(obj[i]))
                j++;
        }

        if (j > 1) return;

        ob = new(CLASS_D("taohua/huang"));
        if (! me->is_busy())
                me->start_busy(1);
        ob->move(environment(me));

        message_sort("$N前面突然出现了一人，身材高瘦，身穿青色布袍，脸色古怪之极，两颗眼珠似乎尚能"
                       "微微转动，除此之外，肌肉口鼻，尽皆僵硬如木石，直是一个死人头装在活人的躯体上。\n\n", me);

        message_sort("$N一见之下，登时一阵凉气从背脊上直冷下来，目光与这张脸孔相触，便都不敢再看，立时将"
                       "头转开，心中怦然而动：莫非这就是祖师爷爷，江湖中传闻的桃花岛主？ 忙上前恭恭敬敬的"
                       "磕了四个头，说道：“孙儿叩见师祖。”黄药师道：“罢了！”并不俯身相扶，却伸左手抓住$N后"
                       "心一提，右掌便向$N肩头拍下。。。\n", me);
        message_sort("$N一见不妙，来不及细想，赶紧身形疾闪，使出一招“海燕腾空”，身体如同为海风所激，向后飘开一丈有余。\n\n", me);
        message_sort("黄药师微一愣，哼了一声道：" + RANK_D->query_rude(me) + "却有几分资质，我就成全你吧。\n\n", me);

        message_sort("$N想要收$n为弟子。\n", ob, me);
        tell_object(me, YEL "如果你愿意拜" + ob->name() + "为师父，用 apprentice 指令。\n" NOR);
        set_temp("huang_recr", 1, me);

        //remove_call_out("finish_recr");
        call_out("finish_recr", 30, me, ob);
}

void finish_recr(object me, object ob)
{
        if (! objectp(ob))
                return;

        if (! objectp(me))
        {
                destruct(ob);
                return;
        }

        if( query("family/master_id", me) != "huang yaoshi" )
        {
                message_vision("$N冷笑一声：" + RANK_D->query_rude(me) + "居然有几分臭架子。说完飘然而去。\n", ob);
                delete_temp("huang_recr", me);
                destruct(ob);
        }
        return;
}
