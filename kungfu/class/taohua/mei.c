// This program is a part of NT MudLIB
// mei.c 梅超风

#include <ansi.h>;
inherit NPC;

#define YINJIAO    "/clone/lonely/yinjiaobian"

mixed ask_skill();
mixed ask_skill1();

void create()
{
        object ob;
        set_name("梅超风", ({ "mei chaofeng", "mei", "chaofeng" }));
        set("title", "黑风双煞");
        set("nickname", WHT "铁尸" NOR);
        set("gender", "女性");
        set("age", 32);
        set("long", "梅超风是黄药师唯一的女弟子，本来极受黄药师疼爱，可\n"
                    "惜她与师兄陈玄风暗生情愫，他们偷了「九阴真经」私奔。\n"
                    "她面色大概因为久居海岛显得黝黑，模样却颇为俏丽。她\n"
                    "在桃花弟子中尤精通鞭法。\n");
        set("attitude", "aggressive");
        set("str", 29);
        set("int", 32);
        set("con", 35);
        set("dex", 31);
        set("max_qi", 4500);
        set("max_jing",3000);
        set("neili", 5000);
        set("max_neili", 5000);
        set("jiali", 200);
        set("level", 20);
        set("combat_exp", 1800000);

        set_skill("claw", 200);
        set_skill("strike", 200);
        set_skill("force", 200);
        set_skill("parry", 220);
        set_skill("dodge", 220);
        set_skill("cuixin-zhang", 200);
          set_skill("jiuyin-baiguzhao", 200);
        set_skill("luoying-shenfa", 200);
        set_skill("whip", 220);
        set_skill("canglang-bian", 220);
        set_skill("martial-cognize", 200);

        map_skill("force", "luoying-xinfa");
        map_skill("whip", "canglang-bian");
        map_skill("parry", "yinlong-bian");
        map_skill("dodge", "luoying-shenfa");
        map_skill("claw", "jiuyin-baiguzhao");
        map_skill("strike", "cuixin-zhang");

        prepare_skill("claw", "jiuyin-zhao");
        prepare_skill("strike", "cuixin-zhang");

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "claw.duo" :),
                (: perform_action, "claw.sha" :),
                (: perform_action, "strike.cui" :),
                (: perform_action, "whip.julang" :),
                (: exert_function, "recover" :),
        }));

        create_family("桃花岛", 2, "被逐弟子");
        set("inquiry", ([
                "铜尸" : "江湖上的人都这么叫我的，你怕不怕？哈哈哈哈。",
                "东邪" : "那是我师父的绰号。",
                "西毒" : "那是与家师齐名的高手之一，是个老毒物，住在白驼山。",
                "南帝" : "段王爷已出家当和尚去了，法名叫一灯。",
                "北丐" : "北丐统领中原的丐帮，势力颇为强大。",
                "黄蓉" : "她是我师父的独女，最是刁蛮任性。",
                "洪七公" : "洪七公武功高强，而且教会郭靖那小儿降龙十八掌，可恨！",
                "梅超风" : "不就是我么？你是白痴啊？",
                "陈玄风" : "他是我的师哥，也是我的夫君，可惜被郭靖那小儿暗算了。",
                "黄药师" : "他是我师父。",
                "九阴真经" : "那是我师父的秘籍！你可别打注意！",
                 "九阴神爪" : (: ask_skill :),
                 "夺命连环爪" : (: ask_skill1 :),
        ]));
        set_temp("apply/damage", 100);
        set_temp("apply/unarmed_damage", 100);
        set_temp("apply/armor", 200);

        setup();
/*
        if (clonep())
        {
                ob = find_object(YINJIAO);
                if (! ob) ob = load_object(YINJIAO);
                if (! environment(ob))
                {
                        ob->move(this_object());
                        ob->wield();
                } else
                {
                        ob = new("/clone/weapon/changbian");
                        ob->move(this_object());
                        ob->wield();
                }
        }
*/
        carry_object("/clone/cloth/bupao")->wear();
        carry_object("/clone/unique/dulong-bian")->wear();
        set("startroom", "/d/yongdeng/shidong");
}

void attempt_apprentice(object ob)
{
        command("滚开！");
}

int accept_fight(object me)
{
        command("say 给我滚开！");
        return 0;
}

int accept_hit(object me)
{
        command("say 找死！");
        kill_ob(me);
        return 1;
}

void kill_ob (object ob)
{
        object me = this_object();
        object where = environment(me);
        object guard = present("chen xuanfeng", where);

        set_temp("my_killer", ob);
        ::kill_ob(ob);

        if (guard && ! guard->is_fighting())
        {
                message_vision(HIW "\n$N" HIW "大怒道：居然欺负到我们黑风双煞"
                               "头上来了，死吧！\n\n" NOR, guard);
                guard->kill_ob(ob);
        }
}

mixed ask_skill1()
{
        object me = this_player();

        if( query("can_perform/jiuyin-baiguzhao/duo", me) )
                return "你不是已经会了吗？";

        if (me->query_skill("jiuyin-baiguzhao", 1) < 150)
        {
               command("shake");
               return "你九阴白骨爪火候不够，我还不能传你这招！";
        }

        if (me->query_skill("claw", 1) < 150)
               return "你基本爪法不够娴熟，我不能传你这招！";

        if (me->query_skill("force", 1) < 150)
               return "你内功修为不够，我不能传你这招！";

        if (me->query_skill("martial-cognize", 1) < 200)
               return "你武学修养不够，我不能传你绝招！";

        if( query("max_neili", me)<2000 )
               return "你内力修为不足，我还不能传你绝招！";

        command("heihei");
        command("say 看清楚了！");
        message_sort(HIR "梅超风桀桀怪笑，手指微微弯曲，倏的冲$N" HIR "头顶抓下，$N" HIR
                     "急忙闪头，然而梅超风这招来得好快，正插中$N" HIR "肩头！\n" NOR, me);
        command("haha");

        command("say 可有看清楚？");
        if (me->can_improve_skill("claw"))
                me->improve_skill("claw", 500000);
        if (me->can_improve_skill("jiuyin-baiguzhao"))
                me->improve_skill("jiuyin-baiguzhao", 500000);
        if (me->can_improve_skill("martial-cognize"))
                me->improve_skill("martial-cognize", 500000);
        set("can_perform/jiuyin-baiguzhao/duo", 1, me);
        tell_object(me, HIG "你学会了「夺命连环爪」！\n" NOR);

        return 1;
}

mixed ask_skill()
{
        object me = this_player();

        if( query("can_perform/jiuyin-baiguzhao/zhua", me) )
                return "你不是已经会了吗？";

        if( !query("can_learn/jiuyin-baiguzhao/zhua", me) )
        {
               tell_object(me, HIG "你去将「九阴真经下册」找来给我，我便传你这招！\n" NOR);
               command("heihei");
               return 1;
        }

        if (me->query_skill("jiuyin-baiguzhao", 1) < 240)
        {
               command("shake");
               return "你九阴白骨爪火候不够，我还不能传你这招！";
        }

        if (me->query_skill("claw", 1) < 240)
               return "你基本爪法不够娴熟，我不能传你这招！";

        if (me->query_skill("force", 1) < 260)
               return "你内功修为不够，我不能传你这招！";

        if (me->query_skill("martial-cognize", 1) < 240)
               return "你武学修养不够，我不能传你绝招！";

        if( query("max_neili", me)<5500 )
               return "你内力修为不足，我还不能传你绝招！";

        command("heihei");
        command("say 小心~~！");
        message_sort(HIM "梅超风左手成爪，尖啸一声，猛然间抓向$N" HIM "的肩膀，$N" HIM
                     "微微一笑，随手招架，只见梅超风左手忽然收回，右手却猛地抓出，速度之"
                     "快，方位之准，直袭$N" HIM "檀中大穴。$N" HIM "只觉得一股阴风袭过，"
                     "早已无力招架，梅超风却突然收招，右手却停留在你檀中穴上，只需要稍稍"
                     "一用力，$N" HIM "便会登时毙命！\n" NOR, me);
        command("haha");

        command("say 明白了吗？");
        if (me->can_improve_skill("claw"))
                me->improve_skill("claw", 1500000);
        if (me->can_improve_skill("jiuyin-baiguzhao"))
                me->improve_skill("jiuyin-baiguzhao", 1500000);
        if (me->can_improve_skill("martial-cognize"))
                me->improve_skill("martial-cognize", 1500000);

        set("can_perform/jiuyin-baiguzhao/zhua", 1, me);
        tell_object(me, HIG "你学会了「九阴神爪」！\n" NOR);

        return 1;
}

int accept_object(object me, object ob)
{
        if (base_name(ob) != "/clone/book/jiuyin2")

        {
               command("say 你给我这种东西干什么？");
               return 0;
        }

        command("heihei");
        command("say 好吧，既然这样，我就传你绝招，你可以随时来问我！");
        tell_object(me, HIG "梅超风决定传你「九阴神抓」！\n" NOR);
        destruct(ob);
        set("can_learn/jiuyin-baiguzhao/zhua", 1, me);

        return 1;
}

void die()
{
        object obj, me;
        int i, flag;

        flag = 0;

        me = this_object();
        if (objectp(obj = query_last_damage_from()))
                set_temp("kill_chaofeng", 1, obj);
        else
                return;

        if( query_temp("kill_xuanfeng", obj) )
        {
                set("kill_th_traitor", 1, obj);
                flag = 1;
        }

        if (flag)
                message_vision(HIR "梅超风惨叫一声，道：贼汉子，我陪你来了！！！\n" NOR, this_object());
        else
                message_vision(HIR "梅超风惨叫一声，道：贼汉子，给我报仇！！！\n" NOR, this_object());

        ::die();
}
