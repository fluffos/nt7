// tanglyz

#include <ansi.h>
#include "tangmen.h"

inherit NPC;
inherit F_MASTER;

void create()
{
        set_name("唐老爷子", ({ "tanglyz", "tang", "yezi"}));
        set("long",
"唐老爷子是唐门的开山祖师，在唐门地位颇高。\n");
        set("gender", "男性");
        set("age", 91);
        set("class", "tangmen");
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("str", 25);
        set("int", 25);
        set("con", 25);
        set("dex", 28);
        set("max_qi", 8000);
        set("max_jingli", 1500);
        set("max_douzhi", 500);
        set("douzhi", 500);
        set("neili", 4000);
        set("max_neili", 4000);
        set("yanli",200);
        set("jiali", 100);
        set("combat_exp", 800000);
        set("level", 15);
        set("shen",3000);
        set("score", 7000);

        set_skill("force", 600);
        set_skill("throwing", 600);
        set_skill("dodge", 600);
        set_skill("parry", 600);
        set_skill("literate", 600);
        set_skill("hand", 600);
        set_skill("hand", 600);
        set_skill("sword", 600);
        set_skill("boyun-suowu", 600);
        set_skill("biyun-xinfa", 600);
        set_skill("sanku-shengong", 600);
        set_skill("qiulin-shiye", 600);
        set_skill("wuzhan-mei", 600);
        set_skill("poison", 5000);
        set_skill("medical", 600);
        set_skill("tangmen-throwing", 600);
        set_skill("tangmen-poison", 600);
        set_skill("tangmen-medical", 600);
        set_skill("luoxian-jue", 600);
        set_skill("martial-cognize", 600);

        map_skill("force", "sanku-shengong");
        map_skill("throwing", "tangmen-throwing");
        map_skill("dodge", "qiulin-shiye");
        map_skill("parry", "wuzhan-mei");
        map_skill("sword", "wuzhan-mei");
        map_skill("hand", "boyun-suowu");
        map_skill("poison", "tangmen-poison");
        map_skill("medical", "tangmen-medical");

        prepare_skill("hand", "boyun-suowu");

        create_family("唐门世家", 1, "掌门");

        set_temp("apply/damage", 100);
        set_temp("apply/unarmed_damage", 100);
        set_temp("apply/armor", 200);

        set("master_ob", 5);
        setup();
        carry_object("/clone/misc/cloth")->wear();
        carry_object("/d/tangmen/obj/feidao")->wield();
        carry_object("/d/tangmen/obj/fhshi")->wield();
        carry_object("/d/tangmen/obj/tiejili")->wield();
        carry_object("/d/tangmen/obj/feidao")->wield();
        carry_object("/d/tangmen/obj/fhshi")->wield();
        carry_object("/d/tangmen/obj/tiejili")->wield();
        carry_object("/d/tangmen/obj/qinglianzi")->wield();
        carry_object("/d/tangmen/obj/qinglianzi")->wield();
        set_temp("handing", carry_object("/d/tangmen/obj/jili"));
}

void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob))
                return;

        if( query("family/family_name", ob) == "唐门世家" && query("combat_exp", ob)>1000000 )
        {
                message_vision("唐老爷子微微一笑，对$N说道:“想拜师的话去找老太太吧，我已经不收徒弟了！”\n",ob);
                message_vision("唐老爷子微微一顿，又道:“不过，既然你已经找到我这里了，我就指点你几招吧！”\n",ob);
                command("say 好吧，从今天起你就是我的关门弟子了。\n");
                command("recruit "+query("id", ob));
        }
        else
                if( query("family/family_name", ob) != "唐门世家" )
                {
                        message_vision("\n唐老爷子微微一笑，对$N说道:“你不知我唐门乃是世家，不收外姓弟子嘛！”\n",ob);
                        message_vision("唐老爷子微微一顿，又道:“不过，既然你已经找到我这里了，就喝杯茶再走吧！”\n",ob);
                        tell_object(ob, "唐老爷子见你有些犹豫，说道:“这茶可是极其珍贵，喝了可以固本培元，对习武之人可是大大的有益啊！”\n\n");
                        write(YEL"你要喝吗？请输入选择（y)/n ："NOR);
                        input_to("accept_cha", 1, ob, 1);
                }
                else
                        tell_object(ob, "唐老爷子惋惜的对你说:“可惜你的功夫还不到家，不能使用我的绝技！你以后再来吧！”\n");
        return;
}

void accept_cha(string want, object ob, int forever)
{
        if ( want == "" || want == "y" || want == "Y" )
        {
                message_vision("唐老爷子微一抬手，便有一家丁给$N奉上了一杯香茶！\n",ob);
                tell_object(ob, "只见茶水发出淡淡的绿色，正冒着热气，几片不知名的叶片漂在杯中，闻起来清香扑鼻。\n");
                message_vision("$N将茶杯端起，美美的喝了一口。\n", ob);
                call_out("dead", 120, ob);
        }
        else
        {
                message_vision("\n唐老爷子勃然大怒，对$N喝道:“让你好死你不要，非要我动手吗！我这里是不能被外人知道的！”\n",ob);
                this_object()->kill_ob(ob);
                ob->fight_ob(this_object());
        }
}

int dead(object ob)
{
        tell_object(ob,HIR"你腹中突然如刀绞一般疼痛，原来茶中竟是剧毒......\n你眼前一黑，一头栽倒在地上......"NOR);
        tell_room(environment(ob),HIR+query("name", ob)+"突然一头栽倒在地上！"NOR,ob);
        set_temp("die_reason", "中唐门奇毒而死", ob);
        ob->die();
        tell_room( environment(this_object()), "唐老爷子长叹一声:“唉！外人怎么会闯进来了呢！”");
}
