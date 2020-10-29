// cheng.c

#include <ansi.h>;

inherit NPC;

#define SHENPIAN    "/clone/book/yaowang"

mixed ask_shenpian();

void create()
{
        set_name("程灵素", ({ "cheng lingsu", "cheng" }));
        set("gender", "女性");
        set("age", 24);
        set("long", @long
她看上去双眉紧缩，不知道有什么心事，长得相貌平平，并不出众。
身材瘦小，穿着粗布衣衫。
long);
        set("attitude", "peaceful");
        set("str", 22);
        set("int", 35);
        set("con", 31);
        set("dex", 27);
        set("chat_chance", 10);
        set("chat_msg", ({
                "程灵素哀哀的叹了口气。\n",
        }));

        set("qi", 2500);
        set("max_qi", 2500);
        set("jing", 1200);
        set("max_jing", 1200);
        set("neili", 2800);
        set("max_neili", 2800);
        set("jiali", 40);
        set("combat_exp", 400000);
     
        set_skill("force", 300);
        set_skill("poison", 5000);
        set_skill("dispel-poison", 1000);
        set_skill("medical", 1000);
        set_skill("baicao-jue", 1000);
        set_skill("yaowang-miaoshu", 1000);

        set("inquiry",([
                "胡斐":     "他...他...\n",
                "袁紫衣":   "我...你提他干什么？\n",
                "药王神篇" : (: ask_shenpian :),
        ]));

        setup();
        carry_object("/clone/cloth/cloth")->wear();
}

int recognize_apprentice(object me, string skill)
{
        if( query("family/family_name", me) != "关外胡家" )
        {
                command("say 你是谁？来干什么？");
                return -1;
        }

        if (skill != "poison" && skill != "dispel-poison" &&
            skill != "medical" && skill != "yaowang-miaoshu")
        {
                command("say 我只会毒功和医术，别的我就没法子教你啦！");
                return -1;
        }

        if( query("shen", me)<0 )
        {
                command("sigh");
                command("say 你怎能走上邪路？我可不能教你毒技。");
                return -1;
        }

        if( !query_temp("can_learn/cheng/poison", me) )
        {
                set_temp("can_learn/cheng/poison", 1, me);
                command("say 看在胡斐你面子上，我就叫你一点本事吧，你可要好自为之！");
                return 1;
        }

        return 1;
}

mixed ask_shenpian()
{
        object me;
        object ob;
        object owner;

        me = this_player();
        if (me->is_bad())
        {
                if( query("family/family_name", me) == "关外胡家" )
                        message_vision(CYN "$N" CYN "冷哼一声，对$n" CYN "道："
                                       "“你难道忘记了你师傅是怎么教你的吗？现在居"
                                       "然和那三个家伙一样走上了邪道，我如何能"
                                       "将《药王神篇》交予你？”\n" NOR,
                                       this_object(), me);
                else
                        message_vision(CYN "$N" CYN "冷笑一声，对$n" CYN "说道"
                                       "：“好一个邪派妖徒，竟敢贪图本派宝物！"
                                       "”\n" NOR,
                                       this_object(), me);
                return 1;
        }

        if( query("family/family_name", me) != "关外胡家" )
                return "你不是关外胡家的，打听它干什么？";

        if( query("shen", me)<100000 )
                return "你侠义正事做得还不够，《药王神篇》我不能给你。";

        if (me->query_skill("medical", 1) < 100)
                return "你基本医术尚未学好，给了你你也读不懂。";

        ob = find_object(SHENPIAN);
        if (! ob) ob = load_object(SHENPIAN);
        owner = environment(ob);
        while (owner)
        {
                if (owner->is_character() || ! environment(owner))
                        break;
                owner = environment(owner);
        }

        if (owner == me)
                return "我这《药王神篇》现在不就在你手里吗？";

        if (objectp(owner) && owner != this_object())
        {
                if (! owner->is_character())
                        return "你来晚了一步，我已经把《药王神篇》借给你同门师兄弟了。";

                if( query("family/master_id", owner) == query("id") )
                        return "嗯，《药王神篇》现在在你同门师兄弟"+query("name", owner)+
                               "手里，你去找他吧。";
                else
                        return "本门的《药王神篇》现在落入了"+query("name", owner)+
                               "之手，你去把它取回来吧！";
        }

        ob->move(this_object());
        message_vision(HIC "$N" HIC "微微一笑，道：“这本《药王神篇》现在"
                       "给你，记住，千万不可用它为非作歹！”\n" NOR,
                       this_object(), me);
        command("give yaowang shenpian to "+query("id", me));
        return 1;
}
