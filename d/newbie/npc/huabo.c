// 离村前设置性格及天赋等数据

#include <ansi.h>

inherit NPC;

mixed ask_chucun();       //请求出村

void create()
{
        set_name(HIC "花伯" NOR, ({ "hua bo", "hua", "bo" }));
        set("long", @LONG
这是一个精干的老者，看起来有八十多岁，他是老村长的徒弟，
如果你要出村，可以找他（ask hua about 出村）。
LONG);        
        set("gender", "男性" );
        set("title", HIR "古村守卫" NOR); 
        set("age", 88);
        set("attitude", "friendly");
        set("max_jing", 5000000);
        set("max_qi", 5000000);
        set("max_jingli", 5000000);
        set("jingli", 5000000);
        set("max_neili", 5000000);
        set("neili", 5000000);
        set("jiali", 600);
        set("str", 100);
        set("int", 100);
        set("con", 100);
        set("dex", 100);
        set("combat_exp", 100000000);

        set("inquiry", ([
                "出村" : (: ask_chucun :),
        ]));

        set_skill("dodge", 800);
        set_skill("unarmed", 800);
        set_skill("force", 800);
        set_skill("parry", 800);
        set_skill("sword", 800);
        set_skill("poison", 800);
        set_skill("medical", 800);
        set_skill("hand", 800);
        set_skill("strike", 800);
        set_skill("staff", 800);
        set_skill("finger", 800);
        set_skill("claw", 800);
        set_skill("blade", 800);
        set_skill("pixie-jian", 800);
        set_skill("literate", 800);
        set_skill("taoism", 800);
        set_skill("buddhism", 800);
        set_skill("jiuyang-shengong", 800);
        set_skill("lingbo-weibu", 800);
        set_skill("qiankun-danuoyi", 800);
        set_skill("xuanming-zhang", 800);
        set_skill("jiuyin-baiguzhao", 800);
        set_skill("dugu-jiujian", 800);
        set_skill("qianzhu-wandushou", 800);
        set_skill("ranmu-daofa", 800);
        set_skill("dagou-bang", 800);
        set_skill("shaolin-yishu", 800);
        set_skill("wudu-qishu", 800);
        set_skill("throwing", 800);
        set_skill("mantian-xing", 800);
        set_skill("idle-force", 800);
        set_skill("sad-strike", 800);

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

        set("no_pk", 1);
	setup();
        carry_object("d/city/obj/cloth")->wear();
}

int accept_fight(object me)
{
          tell_object(me, HIG "这位" + RANK_D->query_respect(me) +
                "，你还是到练武场找人比试吧！\n" NOR);
          return 0;
}

mixed ask_chucun()
{
        object me;
        string msg;

        me = this_player();

        if( !query("newbie_quest_completed/can_out", me) )
                return "没有尊师的允许，我可不敢让你出村！\n";

        if( query("combat_exp", me)>500000 )
        {
                return "对不起，你经验太高了，恐怕我也帮不了你了（经验不能超过50万）！\n";
        }

        msg = HIG "好吧！你选择你要去的地方吧：\n" NOR;
        msg+= HIW "--------------------------------------------\n" NOR;
        msg+= HIC "1. 直接出村（到扬州武庙）\n" NOR;
        msg+= HIC "2. 到郭府历练（到郭府大门外）\n" NOR;
        msg+= HIC "3. 拜师（到门派入门师傅处）\n" NOR;
        msg+= HIC "4. 我还是先在古村四处逛逛吧。\n" NOR;
        msg+= HIW "--------------------------------------------\n" NOR;
        msg+= HIR "请输入1—4编号。\n\n" NOR;

        tell_object(me, msg);

        input_to("get_select", me);
        
        return 1;
}

void get_select(string arg, object me)
{
        string msg;

        if (! arg || arg == "4")return;

        if (arg != "1" && arg != "2" && arg != "3")
        {
                tell_object(me, HIG "请输入 1—4 中的数字！\n");
                input_to("get_select", me);
                return;
        }

        
        if (arg == "1")
        {
                me->move("/d/city/wumiao");
                set("startroom", "/d/city/wumiao", me);

                // 出村给予5万经验10万潜能
                addn("combat_exp", 50000, me);
                addn("potential", 100000, me);
                tell_object(HIG "新手奖励：你成功出古村，获得5万经验和10万潜能的奖励！\n" NOR);
                        
                // 取消拜师标志
                if( query("family/family_name", me) == "古村" )
                delete("family", me);
                delete("title", me);
                set("title", "普通百姓", me);

                // 设置年龄
                set("mud_age", 0, me);
                delete("newbie_quest_completed", me);
                set("out_newbie", 1, me);
                me->save();
                return;
        }
        if (arg == "2")
        {
                me->move("/d/wuguan/guofu_gate");
                tell_object(me, BLINK + HIR "\n输入指令 join 郭府 加入郭府！\n" NOR);
                set("startroom", "/d/wuguan/guofu_gate", me);

                // 出村给予5万经验10万潜能
                addn("combat_exp", 50000, me);
                addn("potential", 100000, me);
                tell_object(HIG "新手奖励：你成功出古村，获得5万经验和10万潜能的奖励！\n" NOR);
                                
                // 取消拜师标志
                if( query("family/family_name", me) == "古村" )
                delete("family", me);
                delete("title", me);
                set("title", "普通百姓", me);
                // 设置年龄
                set("mud_age", 0, me);
                delete("newbie_quest_completed", me);
                set("out_newbie", 1, me);
                me->save();
                return;
        }
        if (arg == "3")
        {
                msg = HIC "请选择你要去的门派（我将送你到门派拜师处）：\n" NOR;
                msg+= HIW "------------------------------------------\n" NOR;
                msg+= HIY "f1.  华山派            f15. 血刀门\n"
                          "f2.  嵩山派(未开放)    f16. 雪山派\n"
                          "f3.  衡山派(未开放)    f17. 丐  帮\n"
                          "f4.  少林派            f18. 铁掌帮(未开放)\n"
                          "f5.  武当派            f19. 红花会(未开放)\n"
                          "f6.  峨嵋派            f20. 五毒教\n"
                          "f7.  逍遥派            f21. 明  教\n"
                          "f8.  灵鹫宫            f22. 玄冥谷(未开放)\n"
                          "f9.  星宿派            f23. 梅  庄(未开放)\n" 
                          "f10. 古墓派            f24. 凌霄城(未开放)\n"
                          "f11. 全真派            f25. 镇远镖局(未开放)\n"
                          "f12. 昆仑派(未开放)    f26. 绝情谷(未开放)\n"
                          "f13. 桃花岛            f27. 日月神教\n"
                          "f13. 药王谷(未开放)    f28. 魔  教\n\n"
                          "s1.  欧阳世家          s2.  中原苗家(未开放)\n"
                          "s3.  慕容世家          s4.  八卦刀商家堡(未开放)\n"
                          "s5.  关外胡家          s6.  大理段氏\n"
                          "s7.  唐门世家\n\n" NOR;
               msg+= HIW "--------------------------------------\n" NOR;
               msg+= HIR "请输入f1—f28，s1—s7编号。\n\n" NOR;

               tell_object(me, msg);
               input_to("get_sel_fam", me);

               return;                
        }
        return;                
        
}

void get_sel_fam(string arg, object me)
{
        
        mapping path;
        string where;

        path = ([
            "f1"    :  "/d/huashan/laojun",
            "f2"    :  "/d/songshan/dadian",
            "f3"    :  "/d/henshan/zhurongdian",
            "f4"    :  "/d/shaolin/guangchang1",
            "f5"    :  "/d/wudang/sanqingdian",
            "f6"    :  "/d/emei/huayanding",
            "f7"    :  "/d/xiaoyao/xiaodao4",
            "f8"    :  "/d/lingjiu/damen",
            "f9"    :  "/d/xingxiu/xxh1",
            "f10"   :  "/d/gumu/mumen", 
            "f11"   :  "/d/quanzhen/jiaobei",
            "f12"   :  "/d/kunlun/guangchang",
            "f13"   :  "/d/taohua/jingshe",
            "f14"   :  "???",
            "f15"   :  "/d/xuedao/shandong2",
            "f16"   :  "/d/xueshan/shanmen",
            "f17"   :  "/d/gaibang/inhole",
            "f18"   :  "/d/tiezhang/guangchang",
            "f19"   :  "/d/huijiang/damen",
            "f20"   :  "/d/wudu/neijin",
            "f21"   :  "/d/mingjiao/shanmen",
            "f22"   :  "/d/xuanminggu/zulin2",
            "f23"   :  "/d/meizhuang/keting",
            "f24"   :  "/d/lingxiao/gate",
            "f25"   :  "/d/beijing/gate",
            "f26"   :  "/d/jueqing/shanzhuang",
            "f27"   :  "0",
            "f28"   :  "/d/yuanyue/damen",
            "s1"    :  "/d/city/beidajie1",
            "s2"    :  "/d/zhongzhou/miaojia_houting",
            "s3"    :  "/d/yanziwu/shuiyun",
            "s4"    :  "/d/shaolin/guangchang1",
            "s5"    :  "/d/guanwai/xiaowu",
            "s6"    :  "/d/dali/neitang",
            "s7"    :  "/d/tangmen/tmdamen",
        ]);

        
        if (! arg)return;

        if (arg == "f14")
        {
                tell_object(me, HIG "药王谷暂时还没开放！\n" NOR);
                get_select("3", me);
                return;
        }
        if (arg == "f25")
        {
                tell_object(me, HIG "镇远镖局暂时还没开放！\n" NOR);
                get_select("3", me);
                return;
        }
        // 日月神教分男女
        if (arg == "f27")
        {
                if( query("gender", me) == "男性" )
                {
                        where = "/d/heimuya/pingdingzhou";
                }
                else
                        where = "/d/heimuya/shenggu";

        }

        if (! stringp(where))where = path[arg];

        if (! stringp(where))
        {
                tell_object(me, HIR "输入编号错误！\n" NOR);
                get_select("3", me);
                return;
        }


        // 出村给予5万经验10万潜能
        addn("combat_exp", 50000, me);
        addn("potential", 100000, me);
        tell_object(HIG "新手奖励：你成功出古村，获得5万经验和10万潜能的奖励！\n"
                        "到扬州武庙(南贤)处输入指令 ask nanxian 新手福利 还可领取新手福利!\n" NOR);
                
        // 取消拜师标志
        if( query("family/family_name", me) == "古村" )
        delete("family", me);
        delete("title", me);
                set("title", "普通百姓", me);
        // 设置年龄
        set("mud_age", 0, me);
        // 取消登陆地点
        set("startroom", where, me);

                delete("newbie_quest_completed", me);
                set("out_newbie", 1, me);
        //write("where = " + where +"\n");
        // 移动过去
        me->move(where);
        me->save();

        return;
}

void init()
{
        object me;

        me = this_player();

        tell_object(me, HIG "\n花伯对你说道：这位" + RANK_D->query_respect(me) +
                "，如果要出村输入 " HIR "ask hua about 出村 \n\n" NOR);

        return;

}
