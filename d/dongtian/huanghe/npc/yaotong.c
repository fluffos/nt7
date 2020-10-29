#include <ansi.h>
#include <medical.h>

inherit NPC;
inherit F_DEALER;

#define MAXQI 9999999999999

int ask_me();

void create()
{
        set_name(YEL"药僮"NOR, ({ "yao tong", "yao", "tong" }));
        set("title", NOR CYN"傀儡商贩"NOR);
        set("gender", "男性");
        set("age", 16);

        set("int", 30);

        set("qi", MAXQI);
        set("max_qi", MAXQI);
        set("jing", MAXQI);
        set("max_jing", MAXQI);
        
        set("combat_exp", MAXQI);
        set("attitude", "heroism");

        set_skill("unarmed", 99);
        set_skill("dodge", 99);
        set_skill("parry", 99);
        set_skill("force", 99);
        set_skill("liandan-shu", 600);
        set_temp("apply/attack", 70);
        set_temp("apply/defense", 70);
        set_temp("apply/damage", 50);

        set("inquiry", ([
                "疗伤"   : (: ask_me  :),
                "heal"   : (: ask_me  :),
        ]));

        set("vendor_goods", ({
                HERB("chaihu"),         // 柴胡
                HERB("chenpi"),         // 陈皮
                HERB("chongcao"),       // 虫草
                HERB("chuanwu"),        // 川乌
                HERB("dahuang"),        // 大黄
                HERB("dangui"),         // 当归
                HERB("duhuo"),          // 独活
                HERB("fangfeng"),       // 防风
                HERB("fuzi"),           // 附子
                HERB("gsliu"),          // 干石榴
                HERB("guiwei"),         // 归尾
                HERB("hafen"),          // 蛤粉
                HERB("heshouwu"),       // 何首乌
                HERB("honghua"),        // 红花
                HERB("huangqi"),        // 黄芪
                HERB("lurong"),         // 鹿茸
                HERB("xiongdan"),       // 熊胆
                HERB("juhua"),          // 菊花
                HERB("lanhua"),         // 兰花
                HERB("lingxian"),       // 灵仙
                HERB("lingzhi"),        // 灵芝
                HERB("mahuang"),        // 麻黄
                HERB("moyao"),          // 没药
                HERB("niuhuang"),       // 牛黄
                HERB("niuxi"),          // 牛膝
                HERB("qianjinzi"),      // 千金子
                HERB("renshen"),        // 人参
                HERB("ruxiang"),        // 乳香
                HERB("shadan"),         // 鲨胆
                HERB("shancha"),        // 山茶花
                HERB("shanjia"),        // 山甲
                HERB("shengdi"),        // 生地
                HERB("shenglg"),        // 生龙骨
                HERB("sumu"),           // 苏木
                HERB("taoxian"),        // 桃仙
                HERB("tenghuang"),      // 藤黄
                HERB("tianqi"),         // 田七
                HERB("tugou"),          // 土狗
                HERB("wulingzhi"),      // 五灵脂
                HERB("xiefen"),         // 蝎粉
                HERB("xijiao"),         // 犀角
                HERB("xionghuang"),     // 雄黄
                HERB("xuejie"),         // 血竭
                HERB("xuelian"),        // 雪莲
                HERB("yanwo"),          // 燕窝
                HERB("yjhua"),          // 洋金花
                HERB("yuanzhi"),        // 远志
                HERB("zihua"),          // 紫花
                HERB("zzfen"),          // 珍珠粉
                HERB("hugu"),           // 虎骨
                "/clone/misc/dymo", 
                "/clone/drug/tianqi-san",
                "/d/city/obj/shanshen",
                "/clone/medicine/jinmisan",
                "/clone/book/medical_book",
        }));

        setup();
        carry_object("/clone/misc/cloth")->wear();
        set("neili", 0);
        set("max_neili", 0);
        set("jingli", 0);
        set("max_jingli", 0);
}

string getname()
{
        return NOR + CYN + query("name") + NOR ;
}

void init()
{
        add_action("do_list", "list");
        add_action("do_buy", "buy");
}

void fullnow(object me)
{
        mapping my;
                me->remove_call_out("revive");
                me->remove_call_out("unconcious");
        my = me->query_entire_dbase();
        my["jing"]   = my["eff_jing"]   = my["max_jing"]; 
        my["jingli"] = my["eff_jingli"] = my["max_jingli"]; 
        my["qi"]     = my["eff_qi"]     = my["max_qi"]; 
        my["neili"]  = my["max_neili"];
        me->clear_condition();
        me->stop_busy();
        me->clear_weak();
        me->full_self();
        if( query_temp("block_msg/all", me) ) {
                        tell_object(me, HIR "你终于抹掉了眼前的鲜血，能看见了。\n" NOR);
                        delete_temp("block_msg/all", me);
        }
}

int ask_me()
{
        object ob = this_player();
        
        if (ob->is_busy() || ob->is_fighting()) {
                write("你现在正忙。\n" NOR);
                return 1;
        }
        
        if (is_fighting() || is_busy()) {
                write(getname() + NOR + "没空理你。\n" NOR);
                return 1;
        }
        
        if( query_temp("dongtian/healme", ob) > time() )
        {
                command("say 这么快... 你又来？");
                command("slap " + query("id", ob));
                ob->start_busy(6);
        }
        else
        {
                message_vision(getname() + CYN + "手指微屈，单指一弹，一粒药丸疾射入$N的咽喉，$N"
                                "不由“咕噜”一声吞入腹中，顿感神清气爽，精神饱满。\n", ob);
                                fullnow(ob);
                                set_temp("dongtian/healme", time() + 1800, ob);
                                ob->start_busy(3);
        }
        
                return 1;
}

int recognize_apprentice(object ob, string skill)
{
        if (skill != "liandan-shu")
                return 0;

        if (ob->query_skillo("liandan-shu", 1) >= 300)
        {
                write(getname() + CYN + 
                                "点了点头，说道：炼丹技艺的提"
                        "高需要不断从实践中来提升的，炼丹技艺的\n"
                        "基本功我就教到这里，剩下看你的天赋和修行了。\n" + NOR);
                return -1;
        }
        return 1;
}

varargs void die(object killer)
{
                message_vision(getname() + CYN + "手指微屈，单指一弹，一粒药丸跳进嘴里吞入腹中，顿感神清气爽，精神饱满。\n", this_object());
                                fullnow(this_object());
                return;
}

void unconcious()
{
    die();
        return;
}
