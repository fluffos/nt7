// This program is a part of NT MudLIB

#include <ansi.h>

inherit NPC;

string *quest_msg = ({
        HIW "北丑长长的出了一口气，然后掏出一张英雄贴来递到你面前……\n" NOR,
        HIW "北丑说道：聚贤庄这个名字，你应该不会陌生吧。\n" NOR,
        HIW "前些时候，游氏兄弟和薛神医在江湖上广发英雄帖，召集天下英雄豪杰共赴聚贤庄，参加武林大会。\n" NOR,
        HIW "这张帖子是给你的，但是你向来四海为家，居无定所，聚贤庄发派帖子的下人就把你的英雄贴送到我这里来了，希望我可以找到你。\n" NOR,
        HIW "至于这次武林大会究竟是为何事，老朽我也不是很清楚，只听说和丐帮有莫大的关系，江湖上的风言耳语，传来传去的，可以相信的已经不多了。\n" NOR,
        HIW "你现在去洛阳找丐帮的徐长老，他会告诉你具体情况的。\n" NOR,
});

int ask_juxianzhuang();

void create()
{
        set_name("北丑", ({ "bei chou", "bei", "chou", "xizi" }));
        set("long", @LONG
这是一个身着戏子打扮的瘦小老头，长得尖嘴
猴腮，天生一副奸相。谁人能知这便是当今武
林中号称「南贤北丑」戏子北丑。虽其排名在
南贤之下，但却也是南贤生平最畏惧之人。
LONG);
        set("nickname", HIW "北戏子" NOR);
        set("title", HIC "武林泰斗" NOR);
        set("gender", "男性" );
        set("age", 68);
        set("attitude", "friendly");
        set("max_jing", 50000);
        set("max_qi", 50000);
        set("max_jingli", 50000);
        set("jingli", 50000);
        set("max_neili", 50000);
        set("neili", 50000);
        set("jiali", 350);
        set("str", 50);
        set("int", 50);
        set("con", 50);
        set("dex", 50);
        set("combat_exp", 12000000);
        set("level", 100);

        set_skill("dodge", 500);
        set_skill("unarmed", 500);
        set_skill("force", 500);
        set_skill("parry", 500);
        set_skill("sword", 500);
        set_skill("poison", 500);
        set_skill("medical", 500);
        set_skill("hand", 500);
        set_skill("strike", 500);
        set_skill("staff", 500);
        set_skill("finger", 500);
        set_skill("claw", 500);
        set_skill("blade", 500);
        set_skill("pixie-jian", 500);
        set_skill("literate", 500);
        set_skill("taoism", 500);
        set_skill("buddhism", 500);
        set_skill("jiuyang-shengong", 500);
        set_skill("lingbo-weibu", 500);
        set_skill("qiankun-danuoyi", 500);
        set_skill("xuanming-zhang", 500);
        set_skill("jiuyin-baiguzhao", 500);
        set_skill("dugu-jiujian", 500);
        set_skill("qianzhu-wandushou", 500);
        set_skill("ranmu-daofa", 500);
        set_skill("dagou-bang", 500);
        set_skill("shaolin-yishu", 500);
        set_skill("wudu-qishu", 500);
        set_skill("throwing", 500);
        set_skill("mantian-xing", 500);
        set_skill("idle-force", 500);
        set_skill("sad-strike", 500);

        map_skill("unarmed", "sad-strike");
        map_skill("force", "jiuyang-shengong");
        map_skill("dodge", "lingbo-weibu");
        map_skill("parry", "qiankun-danuoyi");
        map_skill("hand", "qianzhu-wandushou");
        map_skill("strike", "xuanming-zhang");
        map_skill("claw", "jiuyin-baiguzhao");
        map_skill("sword", "dugu-jiujian");
        map_skill("blade", "ranmu-daofa");
        map_skill("staff", "dagou-bang");
        map_skill("throwing", "mantian-xing");
        map_skill("poison", "wudu-qishu");
        map_skill("medical", "shaolin-yishu");

        prepare_skill("unarmed", "sad-strike");

        set("chat_chance_combat", 200);
        set("chat_msg_combat", ({
                (: perform_action, "sword.po" :),
                (: perform_action, "blade.zhenyan" :),
                (: perform_action, "blade.huo" :),
                (: perform_action, "staff.wugou" :),
                (: perform_action, "staff.chan" :),
                (: perform_action, "staff.ban" :),
                (: perform_action, "unarmed.xiao" :),
                (: perform_action, "parry.nuoyi" :),
                (: perform_action, "dodge.lingbo" :),
                (: perform_action, "throwing.shan" :),
                (: perform_action, "hand.zhugu" :),
                (: perform_action, "strike.wuji" :),
                (: perform_action, "finger.six" :),
                (: perform_action, "finger.zhongheng" :),
                (: perform_action, "claw.zhua" :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),
                (: exert_function, "shield" :),
                (: exert_function, "heal" :),
                (: exert_function, "dispel" :),
                (: exert_function, "regenerate" :),
        }));

        set("inquiry", ([
                "帮派"  :"要创建帮派请先组队，人数不能少于五个，然后 team bunch <帮派名> 就可以了。\n",
                "英雄贴": (: ask_juxianzhuang :),
                "挑战BOSS" : "想挑战BOSS？输入 ask bei chou about <BOSS名称> 即可进入挑战空间", 
        ]) );

        set("chat_chance", 1);
        set("chat_msg",({
                CYN "北丑贼眯眯的说：天算地算不如人算，可是再怎么算戏子我都知道。\n" NOR,
        }));

        setup();
        carry_object("/clone/cloth/cloth")->wear();

/*
        if (! clonep(this_object()))
        {
                move("/d/xiakedao/haibin");
                message_vision(CYN "\n$N" CYN "笑嘻嘻道：来了来了，戏子我来了。\n"
                               NOR, this_object());
                set("startroom", "/d/xiakedao/haibin");
        }
*/
}

void init()
{
        ::init();
        add_action("do_join", "join");
}

int ask_juxianzhuang()
{
        object me = this_player();
        call_out("quest_stage", 0, me, 0);
        return 1;
}

void quest_stage(object ob, int stage)
{

        if (! ob || ! present(ob)) return;

        tell_object(ob, quest_msg[stage]);
        if (++stage < sizeof(quest_msg))
        {
                call_out( "quest_stage", 1, ob, stage );
                return;
        }
        set_temp("juxianzhuang_step", 1, ob);
}

mixed accept_ask(object me, string arg)
{
        int valid;
           
        if( !arg || arg == "" || arg == "all" )
                return 0;
        
        if( arg == "挑战BOSS" || arg == "挑战boss" || arg == "BOSS" || arg == "boss" )
        {
                write(HIW"想要挑战BOSS？输入 ask bei chou about <BOSS名称> 即可进入挑战空间。\n"NOR);
                return 1;
        }
        
        valid = FUBEN_D->valid_enter(me, arg); 
        if( valid >=1 )
                FUBEN_D->enter_fuben(me, arg);
        else {
                if( valid == 0 )
                        write("您实战经验不足，进挑战BOSS恐有不测，还是先历练一下再来吧。\n");
                else if( valid == -1 )
                        write("您经验太高了，就不要进去欺负那些可怜的小怪物了吧。\n");
                else if( valid == -2 )
                        write("游戏中目前并没有开放该BOSS，请您核对后再试。\n");
                else if( valid == -3 )
                        write("挑战BOSS限制IP多重进入，您已经超过最高上限。\n");
                else if( valid == -4 )
                        write("该BOSS被巫师关闭，您暂时无法进入。\n");
                else if( valid == -5 )
                        write("你离上次挑战该BOSS的时间太短，请休息会再来。\n");
                else if( valid == -6 )
                        write("该BOSS必须组队才能进入。\n");
                else if( valid == -7 )
                        write("你的队伍人数超过该BOSS规定的上限。\n");
                else if( valid == -8 )
                        write("该BOSS要求单人挑战，您必须解散队伍方可进入。\n");
        }        
        return 1;
}

void fight_ob(object ob)
{
        if (is_fighting(ob))
                return;

        command("say 哼！不知死活。");
        command("exert powerup");
        command("exert sword");
        ::fight_ob(ob);
}

int accept_fight(object who)
{
        command("say 没兴趣。");
        return 0;
}

int accept_ansuan(object who)
{
        return notify_fail("你刚想暗算，可是眼前一花，看不太清楚。\n");
}

varargs void die(object killer)
{
        full_self();
        return;
}

void unconcious()
{
        die();
}
