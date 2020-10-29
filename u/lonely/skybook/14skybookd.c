// This program is a part of NT MudLIB
/*

 十四天书主线任务如下
≡───────────────────────────────≡
 『当前章节』:第一章
 『当前任务』:搜集白狐皮200张
 『任务描述』:现在可以去找点事去做一做，增加一点江湖声望，您可
              以到风云城的一品居的茶博士那里帮他送送茶，如果有
              足够的耐心可以帮茶博士送完2万次茶。
 『完成条件』:去一品居茶博士那（ask waiter about work）
 『完成等级』:需人物等级大于等于0级
 『任务奖励』:黄金1两
≡────────────────────□  十四天书  □───≡
*/

#include <ansi.h>

inherit F_DBASE;

#define LINE   "------------------------------------------------------------------"

string *keys_gift_list;

private void skill_bonus(object me, object who)
{
        int gongxian;
        string *sk_list = ({
                "wuming-jianfa",
                "wuming-jianfa",
                "wuming-jianfa",
                "wuming-jianfa",
                "wuming-jianfa",
                "liumang-shenquan",
                "liumang-shenquan",
                "liumang-shenquan",
/*
                "qishang-quan",
                "qishang-quan",
                "qishang-quan",
                "qishang-quan",
                "zhuihun-jian",
                "zhuihun-jian",
                "zhuihun-jian",
                "zhuihun-jian",
                "baihua-quan",
                "baihua-quan",
                "baihua-quan",
                "baihua-quan",
                "sougu-yingzhua",
                "sougu-yingzhua",
                "sougu-yingzhua",
                "zhuangzi-wu",
                "shenxing-baibian",
                "hanbing-mianzhang",
                "hanbing-mianzhang",
                "hanbing-mianzhang",
                "xuanming-zhang",
                "xuanming-zhang",
                "xuanming-zhang",
                "shenzhaojing",
                "shenzhaojing",
                "shenzhaojing",
                "mingyu-gong",
                "mingyu-gong",
                "mingyu-gong",
                "shexing-lifan",
                "shexing-lifan",
                "shexing-lifan",
                "baihua-cuoquan",
                "baihua-cuoquan",
*/
        });
        string sk;

        sk = sk_list[random(sizeof(sk_list))];
        if (who->query_skill(sk, 1) > 0)
                return;

        gongxian = 100000;
        if( query("family/gongji", who)<gongxian
        ||  !SKILL_D(sk)->valid_learn(who))
        {
                message_vision("$n赞许的对$N笑了笑，道：“你真是我们" +
                               query("family/family_name", me)+
                               "的佼佼者，我最近研究过" +
                               HIY + to_chinese(sk) + NOR
                               "，\n颇有心得，只可惜你现在尚不足以"
                               "领悟其中奥妙，罢了，罢了。”\n",
                               who, me);
                return;
        }

        message_vision("$n赞许的对$N笑了笑，道：“你真是我们" +
                       query("family/family_name", me)+
                       "的佼佼者，正好我最近研究过" +
                       HIY + to_chinese(sk) + NOR
                       "，\n颇有心得，如果你想学，就传授一些与你吧！”\n",
                       who, me);

        tell_object(who, HIW "\n学习" + to_chinese(sk) + HIW "需要消耗"
                         "你" + chinese_number(gongxian) + "点门派"
                         "贡献，你是否愿意(" HIY "answer Y|N" HIW
                         ")接受？\n\n" NOR);

        // 记录可以领取任务奖励的NPC
        set_temp("quest_gift/npc",query("id",  me), who);

        // 记录任务奖励武功
        set_temp("quest_gift/skill", sk, who);

        // 记录领取该武功所需的门牌贡献
        set_temp("quest_gift/gongxian", gongxian, who);

        return;
}

void special_bonus(object me, object who, mixed arg)
{
        int gongxian;
        // 随机奖励
        string *ob_list = ({
                "/clone/gift/xiandan",
                "/clone/gift/shenliwan",
                "/clone/gift/unknowdan",
                "/clone/gift/xisuidan",
                "/d/item/obj/xuantie",
                "/d/item/obj/wujins",
                "/d/item/obj/butian",
                "/d/item/obj/tiancs",
                "/clone/gift/jinkuai",
                "/clone/fam/pill/neili2",
                "/clone/fam/item/bixue",
                "/clone/quarry/item/zhenzhu",
                "/clone/tessera/cruby",
                "/clone/tessera/ctopaz",
                "/clone/tessera/csapphire",
                "/clone/tessera/cemerald",
                "/clone/tessera/cdiamond",
                "/clone/goods/hanxing-yuntie",
                "/clone/tessera/rune11",
                "/clone/tessera/rune12",
                "/clone/tessera/rune13",
                "/clone/tessera/rune14",
                "/clone/tessera/rune15",
                "/clone/tessera/qinglong",
                "/clone/tessera/baihu",
                "/clone/tessera/zhuque",
                "/clone/tessera/xuanwu",
                "/clone/tessera/qilin",
                "/clone/tessera/mcrystal",
        });

        string un, gift;
        object ob;

        /*
        message_vision("$n对$N微微一笑，道：干得不赖，辛苦"
                       "了，正好我这里有点东西，你就拿去吧。\n",
                       who, me);
        */

        if (stringp(arg))
                gift = arg;
        else

        if( query("quest_count", who) == 1000 )
        {
                gift = ob_list[random(sizeof(ob_list))];
                gongxian = 500;
        } else

        if( query("quest_count", who) == 900 )
        {
                gift = ob_list[random(sizeof(ob_list))];
                gongxian = 300;
        } else

        if( query("quest_count", who) == 800 )
        {
                gift = ob_list[random(sizeof(ob_list))];
                gongxian = 400;
        } else

        if( query("quest_count", who) == 700 )
        {
                gift = ob_list[random(sizeof(ob_list))];
                gongxian = 400;
        } else

        if( query("quest_count", who) == 600 )
        {
                gift = ob_list[random(sizeof(ob_list))];
                gongxian = 500;
        } else

        if( query("quest_count", who) == 500 )
        {
                gift = ob_list[random(sizeof(ob_list))];
                gongxian = 300;
        } else

        if( query("quest_count", who) == 400 )
        {
                gift = ob_list[random(sizeof(ob_list))];
                gongxian = 300;
        } else

        if( query("quest_count", who) == 300 )
        {
                gift = ob_list[random(sizeof(ob_list))];
                gongxian = 200;
        } else

        if( query("quest_count", who) == 200 )
        {
                gift = ob_list[random(sizeof(ob_list))];
                gongxian = 150;
        } else

        if( query("quest_count", who) == 100 )
        {
                gift = ob_list[random(sizeof(ob_list))];
                gongxian = 80;
        } else

        if( query("quest_count", who) == 50 )
        {
                gift = ob_list[random(sizeof(ob_list))];
                gongxian = 30;
        } else

        if( query("quest_count", who) == 30 )
        {
                gift = ob_list[random(sizeof(ob_list))];
                gongxian = 10;
        } else
        {
                gift = ob_list[random(sizeof(ob_list))];
                gongxian = 1;
        }

        ob = new(gift);
        if( query("base_unit", ob) )
                un=query("base_unit", ob);
        else
                un=query("unit", ob);

        if( query("family/gongji", who) >= gongxian )
        {
                message_vision(CYN "$n" CYN "对$N" CYN "微笑道：我这里有一"
                               + un + ob->name() + CYN "，如果你用得着就拿"
                               "去吧。\n" NOR, who, me);

                tell_object(who, HIW "\n获得" + ob->name() + HIW "需要消耗"
                                 "你" + chinese_number(gongxian) + "点门派"
                                 "贡献，你是否愿意(" HIY "answer Y|N" HIW
                                 ")接受？\n\n" NOR);

                // 记录可以领取任务奖励的NPC
                set_temp("quest_gift/npc",query("id",  me), who);

                // 记录任务奖励物品的路径
                set_temp("quest_gift/obj", gift, who);

                // 记录领取该物品所需的门牌贡献
                set_temp("quest_gift/gongxian", gongxian, who);
        } else
                message_vision(CYN "$n" CYN "对$N" CYN "道：正好我这"
                               "里有…嗯…还是算了，相信你也用不到。"
                               "\n" NOR, who, me);
        destruct(ob);

        return ;
}

mapping gift_name = ([
        "exp"         :  "经验",
        "pot"         :  "潜能",
        "mar"         :  "体会",
        "neili"       :  "内力",
        "jingli"      :  "精力",
        "gold"        :  "黄金（存银行)",
        "gongxian"    :  "门派贡献",
        "fuzhong"     :  "负重",
        "riding"      :  "骑术",
        "training"    :  "驭兽术",     
        "hunting"     :  "狩猎技巧",
        "certosina"   :  "镶嵌技艺",
        "weiwang"     :  "威望",
        "score"       :  "阅历",
        "tianfu"      :  "先天天赋",
        "horse"       :  "骑马记录点",
        "quitsave"    :  "下线保存所有物品",
]);

mapping gift_list = ([

        "s1"  :   ([ "达成条件" : "注册你的邮箱",
                     "条件标识" : "email",
                     "条件数值" : 1,
                     "条件描述" : "请您使用指令 register 加上你的完整及真实 email 地址进行注册\n"
                                  HIR "              提示：电子邮件地址是保障你一切权益的依据，包括你密码的丢失情况下，我们\n"
                                  HIR "                    通过你注册的信箱来确认你的身份和归还你的密码。" NOR,
                     "奖励描述" : "jingli:500,neili:1000",
                     "下个奖励" : "1", ]),

        "1"   :   ([ "达成条件" : "了解如何开始玩游戏",
                     "条件标识" : "newbie_mygift/help",
                     "条件数值" : 1,
                     "条件描述" : "输入指令 help start 查看相关资讯",
                     "奖励描述" : "/clone/goods/zhufu_cloth:1,neili:1000",
                     "下个奖励" : "2", ]),

        "2"   :   ([ "达成条件" : "查看自己的方位",
                     "条件标识" : "newbie_mygift/map",
                     "条件数值" : 1,    
                     "条件描述" : "输入指令 map 查看自己所在方位\n"
                                  HIR "              提示：地图中蓝色底色位置为你当前所在位置。" NOR,
                     "奖励描述" : "/clone/goods/zhufu_boots:1,jingli:1000",
                     "下个奖励" : "3", ]),

        "3"   :   ([ "达成条件" : "在线2分钟",
                     "条件标识" : "mud_age",
                     "条件数值" : 120,
                     "条件描述" : "在线达到两分钟",
                     "奖励描述" : "/clone/goods/zhufu_armor:1,/clone/gift/xiandan:15",
                     "下个奖励" : "4", ]),
                     
        "4"   :   ([ "达成条件" : "查看新闻",
                     "条件标识" : "newbie_mygift/news",
                     "条件数值" : 1,    
                     "条件描述" : "输入指令 news 查看游戏新闻",
                     "奖励描述" : "/clone/goods/zhufu_head:1,/clone/gift/xisuidan:15",
                     "下个奖励" : "5", ]),

        "5"   :   ([ "达成条件" : "阅读文选",
                     "条件标识" : "newbie_mygift/wenxuan",
                     "条件数值" : 1,
                     "条件描述" : "输入指令 wenxuan 显示年度文选信息",
                     "奖励描述" : "/clone/goods/zhufu_waist:1,/clone/gift/shenliwan:15",
                     "下个奖励" : "6", ]),
                     
        "6"   :   ([ "达成条件" : "查看 msg 功能",
                     "条件标识" : "newbie_mygift/msg",
                     "条件数值" : 1,
                     "条件描述" : "输入指令 msg 显示最近收到的信息",
                     "奖励描述" : "/clone/goods/zhufu_wrists:1,/clone/gift/unknowdan:15",
                     "下个奖励" : "7", ]),

        "7"   :   ([ "达成条件" : "查询新手导师",
                     "条件标识" : "newbie_mygift/who",
                     "条件数值" : 1,
                     "条件描述" : "输入指令 who -v 显示所有的新手导师",
                     "奖励描述" : "/clone/goods/zhufu_surcoat:1,/clone/item/magicfruit:30",
                     "下个奖励" : "8", ]),
                     
        "8"   :   ([ "达成条件" : "查询所有的附加属性",
                     "条件标识" : "newbie_mygift/istat",
                     "条件数值" : 1,
                     "条件描述" : "输入指令 istat 显示所有的附加属性",
                     "奖励描述" : "/clone/goods/zhufu_sword:1,quitsave:8035200,exp:100000,pot:50000",
                     "下个奖励" : "8s", ]),

        "8s"   :   ([ "达成条件" : "查询所有附加的buff",
                     "条件标识" : "newbie_mygift/stat",
                     "条件数值" : 1,
                     "条件描述" : "输入指令 stat 显示所有的附加buff",
                     "奖励描述" : "/clone/goods/zhufu_blade:1,tianfu:4,/adm/npc/obj/gift:1",
                     "下个奖励" : "9", ]),
                                          
        "9"   :   ([ "达成条件" : "了解能力点作用",
                     "条件标识" : "newbie_mygift/ability",
                     "条件数值" : 1,
                     "条件描述" : "输入指令 help ability 了解能力点作用",
                     "奖励描述" : "jingli:500,neili:1000",
                     "下个奖励" : "9s", ]),
        
        "9s"   :   ([ "达成条件" : "了解天赋技能",
                     "条件标识" : "newbie_mygift/talent",
                     "条件数值" : 1,
                     "条件描述" : "输入指令 talent 了解天赋技能",
                     "奖励描述" : "jingli:500,neili:1000",
                     "下个奖励" : "10", ]),
                                                       
        "10"  :   ([ "达成条件" : "闯荡江湖",
                     "条件标识" : "out_newbie",
                     "条件数值" : 1,    
                     "条件描述" : "从古村离开（从武伯那里学完所有技能并离开）\n" 
                                  HIR "              提示：先去武伯那里学完所有技能。\n"
                                      "              在世界之树输入指令" HIY "ask lao 出村" HIR "，根据提示找到村口的花伯出村。\n" NOR,
                     "奖励描述" : "/clone/goods/dizangshi:1,exp:100000,pot:50000,riding:100,training:100,fuzhong:1",
                     "下个奖励" : "12", ]),
                     
        "12"  :   ([ "达成条件" : "制造如意乾坤袋",
                     "条件标识" : "can_summon/qiankun",
                     "条件数值" : 1,    
                     "条件描述" : "制造如意乾坤袋\n" 
                                  HIR "              提示：在扬州城醉仙楼找到狂风，ask kuang about all，制作如意乾坤袋。\n" NOR,
                     "奖励描述" : "/clone/fam/gift/int3:3,exp:50000",
                     "下个奖励" : "14", ]),

        "14"  :   ([ "达成条件" : "与魔幻兽签订血之盟约",
                     //"条件标识" : "newbie_mygift/warcraft",
                     "条件标识" : "can_whistle",
                     "条件数值" : 1,    
                     "条件描述" : "与魔幻兽签订血之盟约\n" 
                                  HIR "              提示：在扬州城醉仙楼找到狂风，打听魔幻兽的事。\n" NOR,
                     "奖励描述" : "/clone/fam/gift/str3:3,exp:50000,horse:1",
                     "下个奖励" : "16", ]),
                     
        "16"  :   ([ "达成条件" : "利用坐骑瞬间到达北京",  
                     "条件标识" : "newbie_mygift/rideto",
                     "条件数值" : 1,
                     "条件描述" : "利用坐骑瞬间达到北京\n" 
                                  HIR "              提示：ride 魔幻兽，使用指令"HIY" rideto beijing " NOR,
                     "奖励描述" : "/clone/fam/gift/con3:3",
                     "下个奖励" : "18", ]),

        "18"  :   ([ "达成条件" : "使用 chatroom 指令到公共聊天室",  
                     "条件标识" : "newbie_mygift/chatroom",
                     "条件数值" : 1,
                     "条件描述" : "使用指令 chatroom 到公共聊天室\n",
                     "奖励描述" : "/clone/fam/gift/dex3:3",
                     "下个奖励" : "19", ]),

        "19"  :   ([ "达成条件" : "使用 recall back 回到扬州",  
                     "条件标识" : "newbie_mygift/recall",
                     "条件数值" : 1,
                     "条件描述" : "使用指令 recall back 回到扬州客店\n",
                     "奖励描述" : "neili:10000,jingli:5000",
                     "下个奖励" : "20", ]),
                     
        "20"  :   ([ "达成条件" : "了解 bug 回报",  
                     "条件标识" : "newbie_mygift/bug",
                     "条件数值" : 1,
                     "条件描述" : "使用指令 help bug 了解bug回报\n",
                     "奖励描述" : "/clone/medal/study-emblem:1",
                     "下个奖励" : "25", ]),     

        "25"   :   ([ "达成条件" : "使用 do 串连指令",
                     "条件标识" : "newbie_mygift/do",
                     "条件数值" : 1,
                     "条件描述" : "输入 do <串连指令>\n"
                                  HIR "              提示：输入"HIY"help do2"HIR"查看帮助，然后使用指令"HIY" do w,w 或 do 2 w " NOR,
                     "奖励描述" : "/clone/goods/magic-silk:1,certosina:200",
                     "下个奖励" : "30", ]),

        "30"  :   ([ "达成条件" : "使用储物柜",
                     "条件标识" : "newbie_mygift/cangku",
                     "条件数值" : 1,
                     "条件描述" : "到扬州钱庄的储物柜看看吧，了解下怎么使用储物柜\n" 
                                  HIR "              提示：扬州钱庄，输入指令"HIY"cw help"HIR"查看即可。" NOR,
                     "奖励描述" : "/clone/armor/jinsi-shoutao2:1",
                     "下个奖励" : "31", ]),
        
        "31"  :   ([ "达成条件" : "了解游戏中的门派贡献商城",  
                     "条件标识" : "newbie_mygift/fmstore",
                     "条件数值" : 1,
                     "条件描述" : "使用指令 fmstore 了解\n",
                     "奖励描述" : "exp:10000,pot:10000",
                     "下个奖励" : "32", ]),    
 
        "32"  :   ([ "达成条件" : "了解游戏中的军功兑换商城",  
                     "条件标识" : "newbie_mygift/jgstore",
                     "条件数值" : 1,
                     "条件描述" : "使用指令 jgstore 了解\n",
                     "奖励描述" : "exp:10000,pot:10000",
                     "下个奖励" : "33", ]),   

        "33"  :   ([ "达成条件" : "了解游戏中的荣誉兑换商城",  
                     "条件标识" : "newbie_mygift/rystore",
                     "条件数值" : 1,
                     "条件描述" : "使用指令 rystore 了解\n",
                     "奖励描述" : "exp:10000,pot:10000",
                     "下个奖励" : "34", ]),   

        "34"  :   ([ "达成条件" : "了解游戏中的英雄商城",  
                     "条件标识" : "newbie_mygift/ntstore",
                     "条件数值" : 1,
                     "条件描述" : "使用指令 ntstore 了解\n",
                     "奖励描述" : "exp:10000,pot:10000",
                     "下个奖励" : "34s", ]),   

        "34s"  :   ([ "达成条件" : "查询技能各种参数",
                     "条件标识" : "newbie_mygift/combat",
                     "条件数值" : 1,
                     "条件描述" : "输入指令 combat 显示所有技能各种参数信息",
                     "奖励描述" : "neili:10000,jingli:5000",
                     "下个奖励" : "35", ]),
                                                                                                                                                  
        "35"  :   ([ "达成条件" : "拜师成功",
                     "条件标识" : "family/family_name",
                     "条件数值" : 1,
                     "条件描述" : "加入一个喜欢的门派,\n" 
                                  HIR "              提示：有关门派详情参见 help family" NOR,
                     "奖励描述" : "gongxian:10000,score:3000,weiwang:50",
                     "下个奖励" : "40", ]),

        "40"  :   ([ "达成条件" : "查询技能绝招",
                     "条件标识" : "newbie_mygift/skill",
                     "条件数值" : 1,
                     "条件描述" : "输入指令 skill lonely-sword 显示独孤九剑绝招信息",
                     "奖励描述" : "neili:1000,gongxian:5000",
                     "下个奖励" : "40s", ]),

        "40s"  :   ([ "达成条件" : "查询技能战斗信息",
                     "条件标识" : "newbie_mygift/power",
                     "条件数值" : 1,
                     "条件描述" : "输入指令 power 显示当前你激发的技能的命中、防御以及伤害信息",
                     "奖励描述" : "neili:1000,gongxian:5000",
                     "下个奖励" : "45", ]),

        "45"  :   ([ "达成条件" : "造访海龟",
                     "条件标识" : "newbie_mygift/haigui",
                     "条件数值" : 1,
                     "条件描述" : "造访一下新手练功法宝海龟\n" 
                                  HIR "              提示：输入"HIY"rideto"HIR"查看骑马可到达地方，然后"HIY"do rideto nanhai,n,e"HIR"前往。\n" NOR
                                  HIR "                    建议新人打海龟到2000万经验，然后去打神雕到1亿经验。" NOR,
                     "奖励描述" : "neili:1000,gongxian:2000",
                     "下个奖励" : "50", ]),

        "50"  :   ([ "达成条件" : "造访神雕",
                     "条件标识" : "newbie_mygift/shendiao",
                     "条件数值" : 1,
                     "条件描述" : "造访新人练功法宝神雕\n" 
                                  HIR "              提示：输入"HIY"rideto"HIR"查看骑马可到达地方，然后"HIY"rideto shendiao"HIR"前往。\n" NOR
                                  HIR "                    建议新人打神雕到1亿经验，然后去运镖到5亿经验。" NOR,
                     "奖励描述" : "neili:1500,jingli:1000,gongxian:2000",
                     "下个奖励" : "55", ]),

        "55"  :   ([ "达成条件" : "加入帮派",
                     "条件标识" : "bunch",
                     "条件数值" : 1,
                     "条件描述" : "加入任意帮派\n" 
                                  HIR "              提示：可以在聊天频道"HIY"chat 想说的话"HIR"找人入帮，详情查看 help bunch.2\n"
                                      "                    如果没有玩家帮派可以参加npc帮派，详情查看help bunch_quest" NOR,
                     "奖励描述" : "pot:20000,weiwang:5000,neili:500,jingli:500",
                     "下个奖励" : "60", ]),

        "60"  :   ([ "达成条件" : "完成帮派任务",
                     "条件标识" : "bunch_quest",
                     "条件数值" : 1,
                     "条件描述" : "完成所在的帮派发布的帮派任务\n" 
                                  HIR "              提示：有关帮派任务详情参见 help bunch_quest" NOR,
                     "奖励描述" : "exp:20000,weiwang:2000,neili:500,jingli:500",
                     "下个奖励" : "65", ]),
                                          
        "65"  :   ([ "达成条件" : "完成师门任务",
                     "条件标识" : "quest_count",
                     "条件数值" : 1,
                     "条件描述" : "找到门派掌门或任务发布师傅领取师门任务并完成\n" 
                                  HIR "              提示：有关师门任务的详情参见 help quest" NOR,
                     "奖励描述" : "exp:10000,pot:10000,gongxian:5000",
                     "下个奖励" : "70", ]),

        "70"  :   ([ "达成条件" : "寻找帝王符图",
                     "条件标识" : "quest_tuteng",
                     "条件数值" : 1,
                     "条件描述" : "到南贤处打听寻找帝王符图\n"
                                  HIR "              提示：有关寻找帝王符图任务的详情参见 help tuteng" NOR,
                     "奖励描述" : "exp:10000,pot:10000,mar:10000",
                     "下个奖励" : "75", ]), 

        "75"  :   ([ "达成条件" : "进入【原始森林】副本",
                     "条件标识" : "newbie_mygift/fuben",
                     "条件数值" : 1,
                     "条件描述" : "进入【原始森林】副本，从副本中走出\n" 
                                  HIR "              提示：骑马到昆明，找到沼泽边缘输入"HIY"enter door"HIR"进入副本。" NOR,
                     "奖励描述" : "exp:20000,pot:20000",
                     "下个奖励" : "80", ]),
                     
        "80"  :   ([ "达成条件" : "造访干将、莫邪",
                     "条件标识" : "newbie_mygift/ganjiang",
                     "条件数值" : 1,
                     "条件描述" : "拜访一下干将莫邪吧，以后还得经常到这里改造兵器\n" 
                                  HIR "              提示：输入"HIY"rideto"HIR"查看骑马可到达地方，然后"HIY"rideto ganjiang"HIR"前往。" NOR,
                     "奖励描述" : "exp:20000,pot:20000,/clone/money/gold:1",
                     "下个奖励" : "85", ]),

        "85"  :   ([ "达成条件" : "打造装备",
                     "条件标识" : "newbie_mygift/makeweapon",
                     "条件数值" : 1,
                     "条件描述" : "是时候拥有一把属于自己的装备了，打造装备说明参见help equipment", 
                     "奖励描述" : "/clone/armor/shuijing-guan:1",
                     "下个奖励" : "90", ]),

        "90"  :   ([ "达成条件" : "找张天师开光",
                     "条件标识" : "newbie_mygift/kaiguang",
                     "条件数值" : 1,
                     "条件描述" : "将刚签名的装备开光吧，这样随时可以召唤(summon)回来\n" 
                                  HIR "              提示：干将附近找到张天师，使用指令"HIY"show <武器ID>"HIR"，按\n"
                                      "                    照后续提示操作即可进行开光。" NOR,
                     "奖励描述" : "/clone/armor/zhanyao-xunzhang:1",
                     "下个奖励" : "95", ]),

        "95"  :  ([ "达成条件" : "博学多才（一）",
                     "条件标识" : "newbie_mygift/certosina",
                     "条件数值" : 1,
                     "条件描述" : "学习镶嵌技艺到一百级\n" 
                                  HIR "              提示：到干将处学习，指令"HIY"xue gan jiang certosina"HIR"学习。" NOR,
                     "奖励描述" : "/clone/armor/moling-zhiyi:1,/clone/armor/sheyao-ring:1",
                     "下个奖励" : "100", ]),

        "100"  :  ([ "达成条件" : "装备开孔",
                     "条件标识" : "newbie_mygift/notch",
                     "条件数值" : 1,
                     "条件描述" : "将装备进行开孔，开孔后可以镶嵌宝石\n" 
                                  HIR "              提示：干将处notch <装备>，开孔需要的符文详情参见 help rune" NOR,
                     "奖励描述" : "exp:1000000,pot:1000000,/clone/armor/wushi-pifeng:1",
                     "下个奖励" : "110", ]),
                                          
        "110"  :   ([ "达成条件" : "合成任意物品",
                     "条件标识" : "newbie_mygift/combine",
                     "条件数值" : 1,
                     "条件描述" : "查看物品合成公式，合成出一个任意物品\n" 
                                  HIR "              提示：有关合成物品的详情参见 help combine" NOR,
                     "奖励描述" : "exp:10000,pot:10000,gongxian:5000",
                     "下个奖励" : "120", ]),

        "120"  :  ([ "达成条件" : "成为一品炼药师",
                     "条件标识" : "is_alchemy",
                     "条件数值" : 1,
                     "条件描述" : "提升炼丹术到300级\n" 
                                  HIR "              提示：炼丹术到300级后，到平一指那里鉴定炼药师品级。" NOR,
                     "奖励描述" : "exp:100000,pot:100000,/clone/armor/shuijing-guan:1",
                     "下个奖励" : "130", ]),

        "130"  :  ([ "达成条件" : "武学宗师",
                     "条件标识" : "opinion/ultra",
                     "条件数值" : 1,
                     "条件描述" : "挑战成为武学大宗师，说明可参见help feature\n" 
                                  HIR "              提示：骑马依次造访四大宗师，使用指令"HIY"ask <宗师NPC ID> about 评价"HIR"后，根据提示\n"
                                      "                    再输入指令"HIY"fight <宗师NPC ID>"HIR"进行挑战。" NOR,
                     "奖励描述" : "exp:2000000,pot:2000000,mar:2000000",
                     "下个奖励" : "140", ]),
                     
        "140"  :  ([ "达成条件" : "博学多才（二）",
                     "条件标识" : "newbie_mygift/jingluoxue",
                     "条件数值" : 1,
                     "条件描述" : "学习经络学到一百级",
                     "奖励描述" : "pot:5000000,neili:500,jingli:500,gold:500",
                     "下个奖励" : "150", ]),

        "150"  :  ([ "达成条件" : "打通阴跷脉",
                     //"条件标识" : "newbie_mygift/yinqiaomai",
                     "条件标识" : "jingmai",
                     "条件数值" : 1,
                     "条件描述" : "购买阴跷脉所有铜人，打通第一条小周天经脉--阴跷脉\n" 
                                  HIR "              提示：在英雄商店购买阴跷脉所有铜人，详情参见 help chongxue" NOR,
                     "奖励描述" : "/clone/goods/tianshi-charm:1",
                     "下个奖励" : "160", ]),
                                          
        "160"  :  ([ "达成条件" : "打通大小周天经脉",
                     "条件标识" : "breakup",
                     "条件数值" : 1,
                     "条件描述" : "冲穴打通大小周天经脉，你的能力将更大提升。\n" 
                                  HIR "              提示：闭关说明可参见 help zhoutian" NOR,
                     "奖励描述" : "mar:3000000,neili:1000,jingli:1000",
                     "下个奖励" : "170", ]),
        
        "165"  :  ([ "达成条件" : "装备升级上古",
                     "条件标识" : "newbie_mygift/ultimate",
                     "条件数值" : 1,
                     "条件描述" : "将装备进行升级上古，升级后的装备属性大幅度提升\n" 
                                  HIR "              提示：洗上古装备详情参见 help equipment" NOR,
                     "奖励描述" : "pot:3000000,neili:1000,jingli:1000",
                     "下个奖励" : "170", ]),
                                  
        "170"  :  ([ "达成条件" : "装备强化",
                     "条件标识" : "newbie_mygift/qianghua",
                     "条件数值" : 1,
                     "条件描述" : "将装备进行强化，强化后的装备属性大幅度提升\n" 
                                  HIR "              提示：干将处先shou <装备>，看完要求后qianghua <装备>，强化装备详情参见 help qianghua" NOR,
                     "奖励描述" : "pot:3000000,neili:1000,jingli:1000",
                     "下个奖励" : "180", ]),

        "180"  :  ([ "达成条件" : "装备绿化",
                     "条件标识" : "newbie_mygift/dosuit",
                     "条件数值" : 1,
                     "条件描述" : "将装备进行绿化，绿化后的装备组成套装，拥有极品属性\n" 
                                  HIR "              提示：先给干将王者之心，然后dosuit <装备>，绿化装备详情参见 help suit" NOR,
                     "奖励描述" : "exp:5000000,pot:5000000,mar:5000000,/clone/armor/yecha1:1",
                     "下个奖励" : "180s", ]),
        
        "180s"  :  ([ "达成条件" : "获得荣誉1000点",
                     "条件标识" : "honors",
                     "条件数值" : 1000,
                     "条件描述" : "参加各种战场，help zhanchang，为荣誉而战吧！\n", 
                     "奖励描述" : "exp:5000000,pot:5000000,mar:5000000,/clone/armor/yecha1:1",
                     "下个奖励" : "190", ]),
                     
        "190"  :  ([ "达成条件" : "修炼元婴出世",
                     "条件标识" : "animaout",
                     "条件数值" : 1,
                     "条件描述" : "提升你的能力，闭关修炼元婴出世\n" 
                                  HIR "              提示：闭关说明可参见 help closed" NOR,
                     "奖励描述" : "pot:3000000,neili:1000,jingli:1000",
                     "下个奖励" : "200", ]),
            
        "200"  :  ([ "达成条件" : "打通生死玄关",
                     "条件标识" : "death",
                     "条件数值" : 1,
                     "条件描述" : "提升你的能力，闭关打通生死玄关\n" 
                                  HIR "              提示：闭关说明可参见 help closed" NOR,
                     "奖励描述" : "exp:5000000,pot:5000000,mar:5000000,/clone/armor/yecha1:1",
                     "下个奖励" : "210", ]),   
                                   
        "210"  :  ([ "达成条件" : "修炼元神",
                     "条件标识" : "yuanshen",
                     "条件数值" : 1,
                     "条件描述" : "提升你的能力，修炼元神获得天赋技能及悟道\n" 
                                  HIR "              提示：元神修炼说明可参见 help yuanshen" NOR,
                     "奖励描述" : "exp:5000000,pot:5000000,mar:5000000,/clone/goods/qianghua_crystal:1",
                     "下个奖励" : "210s", ]),       
                     
        /*
        "190"  :  ([ "达成条件" : "转世重生",
                     "条件标识" : "reborn/times",
                     "条件数值" : 1,
                     "条件描述" : "武学无止境，唯转世重生突破瓶颈\n" 
                                  HIR "              提示：转世说明可参见 help reborn" NOR,
                     "奖励描述" : "exp:10000000,pot:10000000,mar:10000000",
                     "下个奖励" : "200", ]),
        */
        "210s"  :  ([ "达成条件" : "等待下一个挑战", // 这个版本开发至此，后续开发则从这里开始
                     "条件标识" : "newbie_mygift/waitfor_next1",
                     "条件数值" : 1,
                     "条件描述" : "等待下一个挑战吧，敬请留意后续挑战内容！\n" 
                                  HIR "              提示：任务告一段落，请留意后续任务的通告！" NOR,
                     "奖励描述" : "pot:10000000",
                     "下个奖励" : "210s", ]),
]);

mapping query_gift_list(string n)
{
        if( undefinedp(gift_list[n]) ) return 0;
        return gift_list[n];
}

// 外部调用，用于判断是否有指定任务且触发了完成任务条件检测
public void check_mygift(object me, string quest_flag)
{
        string nquest;
        if( !me || !quest_flag ) return;
        if( !nquest = query("newbie_mygift/cur_quest_number", me) )
                return ;
        
        if( gift_list[nquest]["条件标识"] == quest_flag )
        {
                if( gift_list[nquest]["条件数值"] > 1 )
                        addn(gift_list[nquest]["条件标识"], 1, me);
                else
                        set(gift_list[nquest]["条件标识"], 1, me);
                
                me->save();
        }
        return;
}

void create()
{
        seteuid(getuid());
        set("channel_id", "新人奖励精灵");   
        set("no_clean_up", 1);
        CHANNEL_D->do_channel(this_object(), "sys", "新人奖励系统已经启动。");

        keys_gift_list = keys(gift_list);
}

// 判断字符串是否是物品奖励
int is_obgift(string arg)
{
        if( strsrch(arg, "/") == -1 )
                return 0;
                
        return 1;
}

// 返回 exp:3334 格式的奖励描述
string sub_gift_desc(string arg)
{
        string sdesc, sgift;
        object ob;
        int ncount;
        
        sscanf(arg, "%s:%d", sgift, ncount);
        
        sdesc = "";
        // 判断是否是物品
        if( is_obgift(sgift) )
        {
                if( !objectp(ob = find_object(sgift)) )
                        ob = load_object(sgift);
                        
                if( !ob ) return "error:" + sgift;

                sdesc = filter_color(ob->name()) + "x" + sprintf("%d",ncount);
        }
        else
        {
                sdesc = gift_name[sgift] + "+" + 
                        (ncount >= 10000 ? sprintf("%d万", ncount / 10000):sprintf("%d", ncount));
        }       
        
        return sdesc;
}

// 格式化后的奖励描述
// exp:10000000_pot:10000000_mar:10000000_/clone/armor/zhanyao-xunzhang:1
string gift_desc(string arg)
{
        object ob;
        string sdesc, *keys_list;
        int i;
        
        sdesc = "";
        
        // 判断是否是单个奖励
        if( strsrch(arg, ",") == -1 )
        {       
                sdesc = sub_gift_desc(arg);
        }
        else // 多个奖励
        {
                keys_list = explode(arg, ",");
                
                for( i = 0; i < sizeof(keys_list); i ++ )
                {
                        sdesc += sub_gift_desc(keys_list[i]);
                        if( i < sizeof(keys_list) - 1 )
                                sdesc += "、";
                }
        }
        
        return sdesc;
}

// 显示任务描述
string mygift_string(mapping mygift_map)
{
        string squest, sgift_desc;
        
        squest = HIC + LINE + "\n";
        
        squest += "【任务名称】：" + mygift_map["达成条件"] + "\n";
        squest += "【达成条件】：" + mygift_map["条件描述"] + "\n";
        squest += HIY "【任务奖励】：" + gift_desc(mygift_map["奖励描述"]) + "\n";
        squest += HIC + LINE + "\n" NOR;
        
        return squest;
}

// 分派一个任务
void give_mygift(object me, string s)
{
        string squest;
        
        set("newbie_mygift/cur_quest_number", s, me);
        
        // 提示
        squest = HIR "【你获得新的辅助任务】 指令 " HIY "mygift" HIR" 查看当前辅助任务" + BLINK + HIC "    新任务" + NOR "\n" ;
        squest += mygift_string(gift_list[s]);
        
        tell_object(me, squest);
        
        return;
}


// 给予奖励子功能调用
string sub_gift_send(object me, string arg)
{
        string sdesc, sgift;
        object ob;
        int ncount, i;
        
        sscanf(arg, "%s:%d", sgift, ncount);
        
        sdesc = "";
        // 判断是否是物品
        if( is_obgift(sgift) )
        {
                if( !objectp(ob = find_object(sgift)) )
                        ob = load_object(sgift);

                if( !ob )
                {
                        write(HIR + sgift + "读取错误！\n");
                        log_file("mygiftd", "来自mygiftd：" + sgift + "物品错误！\n");
                        return;
                }
                
                // 给予物品。。。
                // 不能分开使用的物品单独处理
                ob = new(sgift);
                if( !objectp(ob) )
                {
                        write(HIR + sgift + "读取错误-2！\n");
                        log_file("mygiftd", "来自mygiftd：" + sgift + "复制物品错误！\n");
                        return;                 
                }
                if( !ob->query_amount() )
                {
                        for (i = 1; i <= ncount; i ++)
                        {
                                reset_eval_cost();
                                ob->move(me, 1);
                                set("bindable", 3, ob);
                                set("bind_owner", query("id", me), ob);
                                set("set_data", 1, ob);
                                set("auto_load", 1, ob);
                                ob = new(sgift);                                                
                        }
                }
                else
                {
                        ob->set_amount(ncount);
                        ob->move(me, 1);
                        set("bindable", 3, ob);
                        set("bind_owner", query("id", me), ob);
                        set("no_sell", 1, ob);
                        set("set_data", 1, ob);
                        set("auto_load", 1, ob);
                }
                
                
                sdesc = HIY "-获得物品：" +  filter_color(ob->name()) + "x" + sprintf("%d",ncount) + "\n" NOR;
        }
        else
        {
                // 奖励。。。
                switch(sgift)
                {
                        case "exp":
                                addn("combat_exp", ncount, me);
                        break;
                        
                        case "pot":
                                addn("potential", ncount,  me);
                        break;

                        case "mar":
                                addn("experience", ncount, me);
                        break;
                                                
                        case "gongxian":
                                addn("family/gongji", ncount, me);
                        break;
                        
                        case "gold":
                                addn("balance", ncount*10000, me);
                        break;

                        case "neili":
                                addn("drug_addneili", ncount, me);
                                addn("max_neili", ncount,  me);
                                if( query("neili", me)<query("max_neili", me) )
                                        set("neili",query("max_neili",  me), me);
                        break;
                
                        case "jingli":
                                addn("drug_addjingli", ncount, me);
                                addn("max_jingli", ncount, me);
                                if( query("jingli", me)<query("max_jingli", me) )
                                        set("jingli",query("max_jingli", me), me);
                        break;

                        case "fuzhong":
                                addn("add_max_encumbrance", 50000, me);
                        break;
                        
                        case "riding":
                                if( me->query_skill("riding") < ncount )
                                        me->set_skill("riding", ncount);
                        break;
                        
                        case "hunting":
                                if( me->query_skill("hunting") < ncount )
                                        me->set_skill("hunting", ncount);
                        break;

                        case "training":
                                if( me->query_skill("training") < ncount )
                                        me->set_skill("training", ncount);
                        break;

                        case "certosina":
                                if( me->query_skill("certosina") < ncount )
                                        me->set_skill("certosina", ncount);
                        break;
                        
                        case "weiwang":
                                addn("weiwang", ncount, me);
                        break;

                        case "score":
                                addn("score", ncount, me);
                        break;

                        case "tianfu":
                                addn("tianfu", ncount, me);
                        break;
                        
                        case "horse":
                                addn("horse/stone", 1, me);
                        break;
                        
                        case "quitsave":
                                me->set_srv("quit_save", 8035200);
                        break;
                        
                        default:
                                write("类型错误。\n");
                                return;
                        break;
                }
                
                sdesc = HIY "-获得奖励" + gift_name[sgift] + "+" + sprintf("%d",ncount) + "\n" NOR;
        }
        
        return sdesc;
}

// 给予奖励
void give_gift(object me, string arg)
{
        int i, count;
        object ob;
        string *keys_list, sgift, sdesc;
                
        
        set("newbie_mygift/is_running_gift_list_send", 1, me);

        sdesc = "";
        // 判断是否是单个奖励
        if( strsrch(arg, ",") == -1 )
        {       
                sdesc += sub_gift_send(me, arg);
        }
        else // 多个奖励
        {
                keys_list = explode(arg, ",");
                
                for( i = 0; i < sizeof(keys_list); i ++ )
                {
                        sdesc += sub_gift_send(me, keys_list[i]);
                }
        }
        
        delete("newbie_mygift/is_running_gift_list_send", me);
        me->save();
        
        write(sdesc);
        
        return;
}

// /cmds/usr/mygift 调用 
int mygift(object me, string arg)
{
        string squest, nquest;
        string splayer;
        object ob;
        
        int i;
        
        // 显示当前任务
        if( !objectp(me) )return 0;
                
        if( !arg )
        {
                if( !nquest=query("newbie_mygift/cur_quest_number", me) )
                        return notify_fail("你当前没有辅助任务信息！\n");
                
                squest = mygift_string(gift_list[nquest]);
        
                squest = HIG "【当前辅助任务如下】\n" + squest; 
                
                me->start_more(squest);
                
                return 1;               
        }
        
        if( arg == "list" )
        {
                if( !wizardp(me) ) return 0;
                
                // 显示所有奖励任务的详细内容，主要用于校验
                squest = "【校验所有任务】\n";

                for( i = 0; i < sizeof(keys_gift_list); i ++ )
                {
                        squest += mygift_string(gift_list[keys_gift_list[i]]) + "\n";
                }
                
                write(squest);
                
                return 1;
        }
        else if( sscanf(arg, "give %s %s", splayer, nquest) == 2 )
        {
                if( !wizardp(me) ) return 0;
                
                // 手动给玩家分派指定编号的任务
                if( !objectp(ob = find_player(splayer)) )
                        return notify_fail("目标玩家不在线！\n");
                
                if( member_array(nquest, keys_gift_list) == -1 )
                        return notify_fail("没有指定编号的任务，使用 mygift list 查看所有任务列表。\n");
                
                give_mygift(ob, nquest);
                
                return 1;
                
        }
        

        return 1;
        
}

// 外部调用，检查当前是否存在已经完成的任务，来自玩家心跳调用
public void check_curgift(object me)
{
        mapping tmap;
        string nquest;
        
        if( !objectp(me) ) return;
        
        if( !query("newbie_mygift/cur_quest_number", me) )
                return;

        // 正在处理奖励中则返回
        if( query("newbie_mygift/is_running_gift_list_send", me) ) return ;
        
        // 判断是否完成
        nquest=query("newbie_mygift/cur_quest_number", me);
        tmap = gift_list[nquest];
        
        if( !intp(query(tmap["条件标识"], me)) || query(tmap["条件标识"], me) >= tmap["条件数值"] )
        {
                // 发放奖励
                write(HIG + "【" + tmap["达成条件"]+ "】" BLINK + HIM "任务达成：\n" NOR);
                give_gift(me, tmap["奖励描述"]);

                // 给予下一个任务
                give_mygift(me, tmap["下个奖励"]);
        }
        
        return;
}
