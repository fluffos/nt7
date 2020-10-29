// guojing.c 郭靖

#include <ansi.h>

inherit NPC;
int ask_rong();
string sign_up();
void random_move();

void create()
{
        set_name("郭靖", ({"guo jing", "guo", "jing"}));
        set("nickname", HIY"北侠"NOR);
        set("gender", "男性");
        set("age", 41);
        set("long", 
                "他就是人称北侠的郭靖，既是蒙古成吉思汗的金刀驸马，又是\n"
                "江南七怪、全真派马钰道长、「北丐」洪七公和「老顽童」周\n"
                "伯通等人的徒弟，身兼数门武功。\n"
                "他身着一件灰色长袍，体态魁梧，敦厚的面目中透出一股威严\n"
                "令人不由得产生一股钦佩之情。\n");
         set("attitude", "peaceful");

        set("chat_chance", 80);
        set("chat_msg", ({          
                (: random_move :),
        }));
                
        set("str", 40);
        set("int", 20);
        set("con", 38);
        set("dex", 25);

            set("no_get", 1);
            set("no_nuoyi", 1);
            
        set("inquiry", ([
                "周伯通" : "你见到我周大哥了？他现在可好？\n",
                "老顽童" : "周大哥一贯这样，没点正经！\n",
                "洪七公" : "师父除了吃，就是喜欢玩。到处玩，还是为了找吃的。\n",
                "黄药师" : "那是我泰山大人。他云游四海，神龙见首不见尾的。\n",
                "一灯大师" : "在下对大师好生感激。\n",
                "欧阳锋" : "这个老毒物，害死我六位师父，一待襄阳事了，决不与他干休。\n",
                "黄蓉"   : "蓉儿是我的爱妻，你问她做甚？\n",
                "蓉儿"   : "蓉儿就是蓉儿了。你问这么多干嘛？\n",
                "郭芙"   : "这个女儿，又笨又不听话。\n",
                "郭襄"   : "襄儿生于乱世，这辈子又多艰厄。但愿她能快乐一世。\n",
                "郭破虏" : "那是我的小儿子。\n",
                "杨过"   : "过儿确实有出息。\n",
                "马钰"   : "马道长于我有半师之谊。\n",
                "丘处机" : "邱道长义薄云天，是真豪杰。\n",
                "柯镇恶" : "那是我大师父。\n",
                "朱聪"   : "那是我二师父。\n",
                "韩宝驹" : "那是我三师父。\n",
                "南希仁" : "那是我四师父。\n",
                "张阿生" : "那是我五师父。\n",
                "全金发" : "那是我六师父。\n",
                "韩小莹" : "那是我七师父。\n",
                "丐帮"   : "丐帮英雄几百年了，守卫襄阳多亏了他们。\n",
                "拜师"   : "现在蒙古人围攻襄阳，我哪有心情收徒啊！\n",
                "报名"   : (: sign_up :),
                "杀蒙古鞑子" : (: sign_up :),
        ]));

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({ 
                        (: perform_action, "strike.fei" :),
                        (: perform_action, "strike.hui" :),
                        (: perform_action, "strike.qu" :),
                        (: perform_action, "strike.zhen" :),
                        (: exert_function, "shield" :),
                        (: exert_function, "powerup" :),
                        (: exert_function, "recover" :),                        
        }));
        
        set("qi", 600000);
        set("max_qi", 600000);
        set("jing", 600000);
        set("max_jing", 600000);
        set("neili", 120000);
        set("max_neili", 120000);
        set("jiali", 200);
        
        set("combat_exp", 40000000);
        set("score", 200000);
         
        set_skill("force", 1200);                // 基本内功
        set_skill("huntian-qigong", 1200);        // 混天气功
        set_skill("strike", 1200);                // 基本拳脚
        set_skill("xianglong-zhang", 1200);        // 降龙十八掌
        set_skill("dodge", 1200);                // 基本躲闪
        set_skill("jinyan-gong", 1200);                // 金雁功
        set_skill("parry", 1200);                // 基本招架
        set_skill("feixu-jin", 500);
        
        map_skill("force", "huntian-qigong");
        map_skill("strike", "xianglong-zhang");
        map_skill("dodge", "jinyan-gong");
        map_skill("parry", "dragon-strike");
        
        prepare_skill("strike", "xianglong-zhang");
        
        setup();
        
        carry_object("/clone/misc/cloth")->wear();
        
        if (clonep()) keep_heart_beat();
}

string sign_up()
{
        object me;
        int win_times;
        
        me = this_player();

        if (is_fighting())
                return HIR "对不住了，现在在先正忙于对付蒙古鞑子。\n" NOR;
                
        if (! XYWAR_D->sign_up_status())
                return HIR "对不住，现在不能报名！\n" NOR;
        
        if (! me->query_temp("want_sign_up_xiangyang_war"))
        {
                me->set_temp("want_sign_up_xiangyang_war", 1);
                return HIG "你是否决定报名参加襄阳保卫战，如果确定请再输入一次。\n" NOR;
        }

        if (XYWAR_D->if_sign_up(me->query("id")))
        {
                return HIC "不错，阁下保家卫国之心可佳！郭某在此谢过了！\n" NOR;
        }

        command("nod");
        command("say 好好好，我大宋有如此爱国之士，定会将蒙古鞑子驱出中原！");
        command("haha");

        XYWAR_D->sign_up(me->query("id"));
        XYWAR_D->xywar_message(me->name() + "(" + me->query("id") + ")" HIG "已报名加入襄阳保卫战，目前共有 " + 
                                     CHINESE_D->chinese_number(XYWAR_D->n_sign_up()) + " 名江湖义士参加抗击蒙古军！\n" NOR);

        tell_object(me, HIG "你已经成功报名参加本次的襄阳保卫战！\n" NOR);
        tell_object(me, HIR "注意，襄阳保卫战结束请请勿离线，否则将自动取消报名资格！\n" NOR);

        tell_object(me, HIC "\n死亡保护90%已经设置完成，死亡后有90%几率不造成任何损失。\n" NOR);
        
        XYWAR_D->set_no_die(me);

        // 删除以前的随机字串标志        
        win_times = me->query("xywar/win");
        me->delete("xywar");
        me->set("xywar/win", win_times);
        me->save();

        return "誓死保卫襄阳！\n";

}


void die()
{

        XYWAR_D->guojing_message(HIR "襄阳军士们，郭某去也，誓死保卫我襄阳！！！" NOR);
        XYWAR_D->xywar_message("郭靖奋力抵抗蒙古鞑子，不幸战死襄阳，终其一生，为抵抗蒙古鞑子做出了难以磨灭的贡献！");
        XYWAR_D->guojing_die();
        destruct(this_object());
}

void uncoucious()
{
        die();
}

void init()
{
        object me = this_player();
        object env;
        env = environment(this_object());
        
        if (base_name(env) == "/d/xiangyang/guangchang")
                call_out("do_hello", 3, me);
        
        //主动杀蒙古兵
        if (me->query("mgbing"))kill_ob(me);

}

void do_hello(object me)
{
        if (! objectp(me))return;
                
        if (environment(me) != environment(this_object()))return; 
        
        if (! XYWAR_D->sign_up_status())return;
        
        tell_object(me, HIG "\n郭靖对你说道：这位" + RANK_D->query_respect(me) + 
        "，想参加襄阳保卫战，为抗击蒙古鞑自出一份力吗？\n"
        "如果愿意参加襄阳保卫战请向我打听 " HIR "报名" HIG " 的相关信息吧！\n" NOR); 
}

void heart_beat()
{
        if (XYWAR_D->dest_status() == 1)
        {
                destruct(this_object());
                return;
        }
        
        return ::heart_beat();
}

void random_move()
{
        string route;
        object env;
        string max_route;
        mapping doors;
                
        if (query_temp("dest_now"))
        {
                                
                destruct(this_object());
                return;
        }

        if (XYWAR_D->dest_status() == 1)
        {
                set_temp("dest_now", 1);
        }

        // 行进路径方向
        // 需要先设置
        route = query("route");

        env = environment(this_object());

        if (! objectp(env))return;

        // 如果到达中央广场则重新选择
        if (base_name(env) == "/d/xiangyang/guangchang" && XYWAR_D->if_guojing_moved())
        {
                max_route = XYWAR_D->max_min_n_soldier("max");
                doors = XYWAR_D->get_doors();
                this_object()->move(doors[max_route]);

                // 设置移动方向
                set("route", XYWAR_D->re_poision(max_route));
                return;
        }

        // 按照路由列表移动
        if (stringp(route) && XYWAR_D->now_status() == 2)command("go " + route);
}

int recognize_apprentice(object ob, string skill)
{
        if (ob->query("xywar/win") < 6)
        {
                tell_object(ob, HIG "郭靖对你说道：阁下侠义之心不足，郭某可不能贸然传你此招。\n" NOR);
                return -1;
        }

        if (ob->query_skill("jiuyin-shengong", 1) < 1)
        {
                tell_object(ob, HIG "郭靖对你说道：你连九阴神功都不会，怎能领悟飞絮劲的奥妙？\n" NOR);
                return -1;
        }
        
        if (ob->query_skill("feixu-jin", 1) < 400)
        {
                tell_object(ob, HIG "郭靖对你说道：以你目前对飞絮劲的修为，还不足以进一步修炼？\n" NOR);
                return -1;
        }

        return 1;
}
