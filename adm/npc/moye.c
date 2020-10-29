// moye.c  莫邪
// Written by Doing Lu  1998/11/2

inherit NPC;
inherit F_NOCLONE;

#include <ansi.h>

int     ask_me();
int     no_money();

#define ITEM_TYPE       0
#define ITEM_STYPE      1
#define ITEM_UNIT       2
#define ITEM_WEIGHT     3
#define ITEM_POINT      4
#define ITEM_PROP       5

string ask_jinlan();

nosave mapping item_type = ([
//      类型        道具类别  继承文件    单位  分量 点数 特殊变量
        "刀"   : ({ "weapon", "blade",    "把", 150, 100, 0, }),
        "剑"   : ({ "weapon", "sword",    "柄", 150, 100, 0, }),
        "棍"   : ({ "weapon", "club",     "根", 150, 100, 0, }),
        "杖"   : ({ "weapon", "staff",    "根", 150, 100, 0, }),
        "锤"   : ({ "weapon", "hammer",   "把", 350, 100, 0, }),
        "斧"   : ({ "weapon", "axe",      "把", 220, 100, 0, }),
        "鞭"   : ({ "weapon", "whip",     "根", 150, 100, 0, }),
        "暗器" : ({ "weapon", "throwing", "把", 30,  100, 0, }),
        "护甲" : ({ "armor",  "armor",    "张", 150, 80,
                     ([ "armor_prop" : ([ //"parry"   : "apply_armor() / 15 + 1",
                                          "armor"   : "apply_armor()",
                                       ]),
                      ]) }),
        "战衣" : ({ "armor",  "cloth",    "件", 200, 100, 0, }),
        "披风" : ({ "armor", "surcoat",   "件", 100, 50,
                     ([ "armor_prop" : ([ //"dodge"   : "apply_armor() / 15 + 1",
                                          "armor"   : "apply_armor()",
                                       ]),
                      ]) }),
        "靴子" : ({ "armor",  "boots",    "双", 60,  40,
                     ([ "armor_prop" : ([ //"dodge"   : "apply_armor() / 10 + 1",
                                          "armor"   : "apply_armor()",
                                       ]),
                      ]) }),
        "头盔" : ({ "armor",  "head",     "顶", 75,  50,  0, }),
        "腰带" : ({ "armor",  "waist",    "条", 80,  40,  0, }),
        "护腕" : ({ "armor",  "wrists",   "对", 50,  25,
                     ([ "armor_prop" : ([ //"sword"   : "apply_armor() / 6 + 1",
                                          //"staff"   : "apply_armor() / 6 + 1",
                                          //"blade"   : "apply_armor() / 6 + 1",
                                          //"club"    : "apply_armor() / 6 + 1",
                                          //"hammer"  : "apply_armor() / 6 + 1",
                                          //"whip"    : "apply_armor() / 6 + 1",
                                          //"dagger"  : "apply_armor() / 6 + 1",
                                          //"stick"   : "apply_armor() / 6 + 1",
                                          //"unarmed" : "apply_armor() / 6 + 1",
                                          //"claw"    : "apply_armor() / 6 + 1",
                                          //"cuff"    : "apply_armor() / 6 + 1",
                                          //"hand"    : "apply_armor() / 6 + 1",
                                          //"strike"  : "apply_armor() / 6 + 1",
                                          //"finger"  : "apply_armor() / 6 + 1",
                                          //"parry"   : "apply_armor() / 6 + 1",
                                          //"whip"    : "apply_armor() / 6 + 1",
                                          "armor"   : "apply_armor()",
                                       ]),
                      ]) }),
        "箫"   : ({ "weapon", "xsword",   "支", 30,  100, 0, }),
        "铁掌" : ({ "armor",  "hands",    "双", 45,  100,
                    ([ "armor_prop" : ([  //"hand"   : "10",
                                          //"strike" : "10",
                                          "unarmed_damage" : "apply_damage()",
                                          "armor"  : "10",
                                       ]),
                     ]) }),
        "护手" : ({ "armor",  "hands",    "双", 40,  100,
                    ([ "armor_prop" : ([  //"unarmed": "10",
                                          //"cuff"   : "10",
                                          "unarmed_damage" : "apply_damage()",
                                          "armor"  : "10",
                                       ]),
                     ]) }),
        "指套" : ({ "armor",  "finger",   "套", 35,  100,
                    ([ "armor_prop" : ([  //"claw"   : "10",
                                          //"finger" : "10",
                                          "unarmed_damage" : "apply_damage()",
                                          "armor"  : "10",
                                       ]),
                     ]) }),
]);

void create()
{
        set_name("莫邪", ({ "mo ye", "moye", "mo" }));
        set("long", "她长得清美秀丽，一副不食人间烟火的模样。她就是铸剑大师干将的妻子。\n" );

        set("nickname", HIY "剑仙" NOR);
        set("gender", "女性");
        set("attitude", "friendly");

        set("age", 1525);
        set("shen_type", 0);

        set("str", 1000);                       // 保证不会因为负荷过大而接受不了东西

        set("inquiry", ([
                "炼制" : (: ask_me :),
                "铸剑" : (: ask_me :),
                "炼剑" : (: ask_me :),
                "炼刀" : (: ask_me :),
                "炼杖" : (: ask_me :),
                "炼鞭" : (: ask_me :),
                "炼棍" : (: ask_me :),
                "炼甲" : (: ask_me :),
                "打造" : (: ask_me :),
                "铸造" : (: ask_me :),
                "制造" : (: ask_me :),
                "打制" : (: ask_me :),
                "定制" : (: ask_me :),
                "定做" : (: ask_me :),
                "定造" : (: ask_me :),
                "兵器" : (: ask_me :),
                "道具" : (: ask_me :),
                "装备" : (: ask_me :),
                "武器" : (: ask_me :),
                "刀剑" : (: ask_me :),
                "装甲" : (: ask_me :),

                "没钱" : (: no_money :),
                "钱不够":(: no_money :),
                "等会" : (: no_money :),
                "锦镧袈裟" : (: ask_jinlan :),

                "销毁" : "那你就把东西给干将，他来做主。",
                "退货" : "那你就把东西给干将，他来做主。",
                "原料" : "炼制道具可不能没有原料啊，要想炼制好武器就得有"
                         "海底金母一类的东西。\n          要想炼制好防具就"
                         "得有寒丝羽竹那些东西。这些原料很难找，可遇不可求啊！\n",
                "价格" : "你把原料给我看看(show)，我就能估摸出一个价钱。",
        ]));

        setup();

        set("startroom", "/d/item/xiaowu");
        check_clone();
        if (! this_object()) return;

        carry_object("/clone/misc/cloth")->wear();
}
// 制作锦镧袈裟
string ask_jinlan()
{
        object me = this_player();
        object ob_jinzhipg, ob_yinzhipg, ob_liangzhipg, ob_xiangbianpg, ob_hongzhipg;
        object ob_lanzhipg, ob_foguangbz, ob_shenzhizs, ob_shenzhifc, ob_shenzhisj, ob_shenzhimn;
        object ob;
        
        int i;
        
        if ( query("reborn/times", me) < 3 )
                return "你好象还没有悟道吧，看来这锦镧袈裟并不适合你。\n";

        // 看是否有可取锦镧袈裟标志，并且时间超过了24小时
        if (query("badao_quest/qu_jiasha", me))
        {
                // 可以取袈裟了
                if (time() - query("badao_quest/qu_jiasha", me) > 0)
                {
                        ob = new("/clone/armor/jinlan-jiasha");
                        
                        // 如果掉在地上设置10分钟内其他人不能拣                 
                        set("who_get", ([
                                "id"     : query("id", me),
                                "time"   : 600,
                        ]), ob);
                        ob->move(me, 1);
                        command("smile " + query("id", me));
                        command("say 阁下来得正好，你要的东西我已经做好了，请收下吧！");
                        message_vision(HIC "$N" HIC "拿出" + ob->name() + HIC "给$n" HIC "。\n", 
                                       this_object(), me); 
                        delete("badao_quest/qu_jiasha", me);
                        me->save();
                        
                        return "好了，你我从此两不相欠，保重！\n";
                }
                else
                        return "你的锦镧袈裟还没有制作完成呢，请 " + HIY + 
                               chinese_number((query("badao_quest/qu_jiasha", me) - time()) / 3600) + 
                               NOR + CYN " 个小时后再来吧。\n";
                
        }

        // 需要材料
          /*
           *金质皮革 10 张
           *银质皮革 10 张
           *亮质皮革 10 张
           *镶边皮革 10 张
           *红质皮革 10 张
           *蓝质皮革 10 张
           *佛光宝珠 10 粒
           *神之钻石 1  粒
           *神之玛瑙 1  粒
           *神之水晶 1  粒
           *神之翡翠 1  粒
           */
       
        command("nod");
        command("say 天下间，只有在下能制作锦镧袈裟，不过需要一些特别的材料：");
        message_vision(HIM  + "\n"
                "*金质皮革 10 张\n"
                "*银质皮革 10 张\n"
                "*亮质皮革 10 张\n"
                "*镶边皮革 10 张\n"
                "*红质皮革 10 张\n"
                "*蓝质皮革 10 张\n"
                "*佛光宝珠 10 粒\n"
                "*神之钻石 5  粒\n"
                "*神之玛瑙 5  粒\n"
                "*神之水晶 5  粒\n"
                "*神之翡翠 5  粒\n"
                "还有手工费用 黄金 10 万两（YSG）\n" NOR, this_object());
        command("say 如果你这些材料都备齐了的话就来找我吧！");
        
        if (! query_temp("want_make_jinlanjiasha", me))
        {
                set_temp("want_make_jinlanjiasha", 1, me);
                return "怎么样？如果你考虑好了，再来找我！\n";          
        }

        // 需要金质皮革 10 
        if (! objectp(ob_jinzhipg = present("jinzhi pige", me)))
                return "你好象还没备齐金质皮革吧？\n";                  
        if (base_name(ob_jinzhipg) != "/clone/quarry/item/combine/jinzhi-pige")
                return "你好象还没备齐金质皮革吧？\n";

        if (ob_jinzhipg->query_amount() >= 10)
        {
                //ob_jinzhipg->add_amount(-10);
                //if (ob_jinzhipg->query_amount() < 1)destruct(ob_jinzhipg);
        }
        else
        {
                return "怎么样，10张金质皮革备齐了吗？\n";
        }


        // 需要银质皮革 10 
        if (! objectp(ob_yinzhipg = present("yinzhi pige", me)))
                return "你好象还没备齐银质皮革吧？\n";                  
        if (base_name(ob_yinzhipg) != "/clone/quarry/item/combine/yinzhi-pige")
                return "你好象还没备齐银质皮革吧？\n";

        if (ob_yinzhipg->query_amount() >= 10)
        {
                //ob_yinzhipg->add_amount(-10);
                //if (ob_yinzhipg->query_amount() < 1)destruct(ob_yinzhipg);
        }
        else
        {
                return "怎么样，10张银质皮革备齐了吗？\n";
        }

        // 需要亮质皮革 10 
        if (! objectp(ob_liangzhipg = present("liangzhi pige", me)))
                return "你好象还没备齐亮质皮革吧？\n";                  
        if (base_name(ob_liangzhipg) != "/clone/quarry/item/combine/liangzhi-pige")
                return "你好象还没备齐亮质皮革吧？\n";

        if (ob_liangzhipg->query_amount() >= 10)
        {
                //ob_liangzhipg->add_amount(-10);
                //if (ob_liangzhipg->query_amount() < 1)destruct(ob_liangzhipg);
        }
        else
        {
                return "怎么样，10张亮质皮革备齐了吗？\n";
        }

        // 需要蓝质皮革 10 
        if (! objectp(ob_lanzhipg = present("lanzhi pige", me)))
                return "你好象还没备齐蓝质皮革吧？\n";                  
        if (base_name(ob_lanzhipg) != "/clone/quarry/item/combine/lanzhi-pige")
                return "你好象还没备齐蓝质皮革吧？\n";
                
        if (ob_lanzhipg->query_amount() >= 10)
        {
                //ob_lanzhipg->add_amount(-10);
                //if (ob_lanzhipg->query_amount() < 1)destruct(ob_lanzhipg);
        }
        else
        {
                return "怎么样，10张蓝质皮革备齐了吗？\n";
        }

        // 需要红质皮革 10 
        if (! objectp(ob_hongzhipg = present("hongzhi pige", me)))
                return "你好象还没备齐红质皮革吧？\n";                  
        if (base_name(ob_hongzhipg) != "/clone/quarry/item/combine/hongzhi-pige")
                return "你好象还没备齐红质皮革吧？\n";

        if (ob_hongzhipg->query_amount() >= 10)
        {
                //ob_hongzhipg->add_amount(-10);
                //if (ob_hongzhipg->query_amount() < 1)destruct(ob_hongzhipg);
        }
        else
        {
                return "怎么样，10张红质皮革备齐了吗？\n";
        }               

        // 需要镶边皮革 10 
        if (! objectp(ob_xiangbianpg = present("xiangbian pige", me)))
                return "你好象还没备齐镶边皮革吧？\n";                  
        if (base_name(ob_xiangbianpg) != "/clone/quarry/item/combine/xiangbian-pige")
                return "你好象还没备齐镶边皮革吧？\n";

        if (ob_xiangbianpg->query_amount() >= 10)
        {
                //ob_xiangbianpg->add_amount(-10);
                //if (ob_xiangbianpg->query_amount() < 1)destruct(ob_xiangbianpg);
        }
        else
        {
                return "怎么样，10张镶边皮革备齐了吗？\n";
        }
        
        // 需要佛光宝珠 10 
        if (! objectp(ob_foguangbz = present("foguang baozhu", me)))
                return "你好象还没备齐佛光宝珠吧？\n";                  
        if (base_name(ob_foguangbz) != "/clone/quarry/item/combine/foguang-baozhu")
                return "你好象还没备齐佛光宝珠吧？\n";

        if (ob_foguangbz->query_amount() >= 10)
        {
                //ob_foguangbz->add_amount(-10);
                //if (ob_foguangbz->query_amount() < 1)destruct(ob_foguangbz);
        }
        else
        {
                return "怎么样，10个佛光宝珠备齐了吗？\n";
        }

        // 需要神之水晶 1 
        if (! objectp(ob_shenzhisj = present("magic crystal", me)))
                return "你好象还没备齐神之水晶吧？\n";                  
        if (base_name(ob_shenzhisj) != "/clone/gift/mcrystal")
                return "你好象还没备齐神之水晶吧？\n";                   
                        
        // 需要神之翡翠 1
        if (! objectp(ob_shenzhifc = present("magic jade", me)))
                return "你好象还没备齐神之翡翠吧？\n";                  
        if (base_name(ob_shenzhifc) != "/clone/gift/mjade")
                return "你好象还没备齐神之翡翠吧？\n";
        
        // 需要神之钻石 1 
        if (! objectp(ob_shenzhizs = present("magic diamond", me)))
                return "你好象还没备齐神之钻石吧？\n";                  
        if (base_name(ob_shenzhizs) != "/clone/gift/mdiamond")
                return "你好象还没备齐神之钻石吧？\n";
        
        // 需要神之玛瑙 1 
        if (! objectp(ob_shenzhimn = present("magic agate", me)))
                return "你好象还没备齐神之玛瑙吧？\n";                  
        if (base_name(ob_shenzhimn) != "/clone/gift/magate")
                return "你好象还没备齐神之玛瑙吧？\n";   
        
        // 需要黄金10万两
        if (query("balance", me) < 100000)
                return "你好象没有备齐10万两黄金吧。\n";       
 
        // 消耗材料
        ob_jinzhipg = present("jinzhi pige", me);
        ob_yinzhipg = present("yinzhi pige", me);
        ob_lanzhipg = present("lanzhi pige", me);
        ob_hongzhipg = present("hongzhi pige", me);
        ob_liangzhipg = present("liangzhi pige", me);
        ob_xiangbianpg = present("xiangbian pige", me);
        ob_foguangbz = present("foguang baozhu", me);
                
        ob_jinzhipg->add_amount(-10);
        if (ob_jinzhipg->query_amount() < 1)destruct(ob_jinzhipg);
        ob_yinzhipg->add_amount(-10);
        if (ob_yinzhipg->query_amount() < 1)destruct(ob_yinzhipg);
        ob_lanzhipg->add_amount(-10);
        if (ob_lanzhipg->query_amount() < 1)destruct(ob_lanzhipg);
        ob_hongzhipg->add_amount(-10);
        if (ob_hongzhipg->query_amount() < 1)destruct(ob_hongzhipg);
        ob_liangzhipg->add_amount(-10);
        if (ob_liangzhipg->query_amount() < 1)destruct(ob_liangzhipg);
        ob_xiangbianpg->add_amount(-10);
        if (ob_xiangbianpg->query_amount() < 1)destruct(ob_xiangbianpg);
        ob_foguangbz->add_amount(-10);
        if (ob_foguangbz->query_amount() < 1)destruct(ob_foguangbz);  

        ob_shenzhifc = present("magic jade", me);
        ob_shenzhizs = present("magic diamond", me);
        ob_shenzhimn = present("magic agate", me);
        ob_shenzhisj = present("magic crystal", me);
                
        destruct(ob_shenzhifc);
        destruct(ob_shenzhizs);
        destruct(ob_shenzhimn);
        destruct(ob_shenzhisj);
        
        addn("balance", -100000, me);                
        
        //log_file("badao_quest_jiasha", query("id". me) + " 制作锦镧袈裟成功！\n");
        
        command("say 不错，不错，这些材料居然你都找齐了，拿我就先收下了。");
        command("say 既然你材料和工钱我都收了，这锦镧袈裟就由我莫邪代劳吧。");
        command("say 不过，制作锦镧袈裟耗时很长，阁下请于24小时后再来取吧。");
        
        // 设置24小时后可取锦镧袈裟
        set("badao_quest/qu_jiasha", time() + 24 * 3600, me);
                
        tell_object(me, HIG "恭喜你，莫邪已经答应帮你制作锦镧袈裟，请于24小时后来取(ask mo about 锦镧袈裟)！\n" NOR);        
        
        delete_temp("want_make_jinlanjiasha", me);
        
        me->save();
        
        return "记住，可别忘了。\n";    
}


void init()
{
        object me;

        // 清除询问标志
        if (! objectp(me = this_player()) || ! interactive(me))
                return;

        add_action("do_show", "show");
        add_action("do_answer", "answer");
        if( query_temp("item/status", me) == "item_gived" )
        {
                remove_call_out("greeting2");
                call_out("greeting2", 1, me);
        } else
        {
                remove_call_out("greeting");
                call_out("greeting", 1, me);
        }
}

void greeting(object me)
{
        if (objectp(me) && environment(me) == environment())
        {
                message_vision("$N笑着对$n说：你好，你是想打造道具"
                               "吗？\n", this_object(), me);
        }
}

void greeting2(object me)
{
        if (objectp(me) && environment(me) == environment())
        {
                message_vision("$N对$n说：交钱就可以打造了哦。\n",
                               this_object(), me);
        }
}

int do_show(string arg)
{
        object  me;
        object  ob;
        string  msg;
        string  mat;
        int     power_point;
        int     value;
        int     n;

        me = this_player();
        if (! arg)
                return notify_fail("你想干什么，是要跳个舞么？\n");

        // 先取下面具
        if (query_temp("apply/name", me))
	        return notify_fail("阁下为何不以真面目示人？\n");
		
        mat = arg;
        power_point = 0;

        if (! objectp(ob = present(mat, me)))
                return notify_fail("算了吧，你身上没有 " + mat + " 这种东西。\n");

        if( !query("material_attrib", ob) )
        {
                message_vision("$N一愣，对$n说道：这种东西也能用来炼"
                               "制，我没听说过。\n", this_object(), me);
        }

        power_point=query("power_point", ob);
        if (! power_point)
        {
                message_vision("$N仔细的看了看$n拿出的原料，叹道："
                               "这样原料看来已经是锻造不了了。\n",
                               this_object(), me);
                return 1;
        }
        value = power_point * 2 + 10;
        msg = sprintf("$N仔细看了看$n拿出的原料，说道：这种原料打造道具，\n" +
                      "只需要%s两黄金，怎么样，我们价格很合理吧。要是没问题"
                      "，请给我原料并付钱。\n", chinese_number(value));
        message_vision(msg, this_object(), me);

        return 1;
}

// 发出提示信息
int ask_me()
{
        message_vision("$N对$n说道："
                "你是要打造自己的道具吗？\n"
                "我们这里可以为你打造各种武器包括刀、剑、鞭、杖和护甲，都是第一流的。\n"
                "你先把原料给我看看(show)，我先估算一下价钱。如果你满意"
                "咱们就一手交钱，一手交货！\n", this_object(), this_player());
        return 1;
}

int no_money()
{
        object me;
        object ob;

        me = this_player();
        if( query_temp("item/status", me) == "item_gived" )
        {
                message_vision("$N打量了一下$n道：没钱那就下次吧！\n",
                               this_object(), me);
                if (objectp(ob = query_temp("item/accept")))
                {
                        message_vision("$N把" + ob->name() +
                                       "交还给$n。\n", this_object(), me);
                        if (! ob->move(me))
                                ob->move(environment());
                }
                delete_temp("item");
                delete_temp("item", me);
                return 1;
        }

        message_vision("$N眼睛一瞪，对$n说道：没钱？你没钱关我啥事，"
                       "我又不是财神爷。\n", this_object(), me);
        return 1;
}

// 接受定金
int accept_object(object me, object ob)
{
        string *types, type;        
        string status;
        int    val;

        // 先取下面具
        if (query_temp("apply/name", me))
	        return notify_fail("阁下为何不以真面目示人？\n");
	                
        /*
        if( query("level", me)<10 )
        {
                message_vision("$N遗憾的对$n说：打造神兵利器必须人物等级达到10级方可。\n",
                               this_object(), me);
                return 0;
        }
        */
        
        status = query_temp("item/status");
        if (status == "look_working")
        {
                message_vision("$N紧张的对$n说：别吵，干将正在干活呢。\n",
                               this_object(), me);
                return 0;
        }

        if (status == "waiting")
        {
                if( query_temp("item/player_id") == query("id", me) )
                {
                        command("say 你好好和干将谈，少打岔！");
                        return 0;
                }

                message_vision("$N对$n说：别吵，干将正在和顾客谈话呢。\n",
                               this_object(), me);
                return 0;
        }

        if (status == "accept")
        {
                if( query_temp("item/player_id") != query("id", me) )
                {
                        command("say 我正在和别的客人商量呢，你先别添乱！");
                        return 0;
                }
                
                if( !ob->is_can_merge() )
                {
                        command("say 你还是快点给我精魂石碎片吧，要是没有就明说！");
                        return 0;
                }
        }
        
        if (status == "accept2")
        {
                if( query_temp("item/player_id") != query("id", me) )
                {
                        command("say 我正在和别的客人商量呢，你先别添乱！");
                        return 0;
                }

                if( !query("money_id", ob) )
                {
                        command("say 你还是快点交钱吧，要是没钱就明说！");
                        return 0;
                }
        }

        if( query("material_attrib", ob) && 
            query("power_point", ob) )
        {
                message_vision("$N对$n说道：很好，现在就差精魂石碎片了，给我吧。\n",
                               this_object(), me);

                // 计算价值
                val=query("power_point", ob)*2+10;
                message_vision("$N接着对$n说道：凑齐打造原料后还要再给我" +
                               chinese_number(val) + "两黄金。\n",
                               this_object(), me);
                val *= 10000;
                if (wizardp(me))
                {
                        message_vision("$N仔细看了看$n，笑着说道：原"
                                       "来是巫师，那么你到时随便给点好了。\n",
                                       this_object(), me);
                        val = 1;
                }
                             
                set("item/value", val, ob);
                set_temp("item/status", "item_gived", me);
                set_temp("item/value", val, me);
                set_temp("item/status", "accept");
                set_temp("item/player_id", query("id", me));
                set_temp("item/accept", ob);

                // 如果过一段时间没有交款，还道具粗坯
                remove_call_out("time_out");
                call_out("time_out", 60, me, ob);
                return 1;
        }
        if( query("id", ob) == "jinghun shi" && 
            ob->is_can_merge() )
        {
                object origin;
                mixed p;
                
                if( query_temp("item/status", me) != "item_gived" )
                {
                        message_vision("莫邪眼睛一瞪，对$N说道：你给我这些东西干什么？我不要！\n", me);
                        return 0;
                }
                
                origin = query_temp("item/accept");
                if( (p=query("can_make", origin)) == "all" )
                {
                        types = keys(item_type);
                } else
                if (arrayp(p))
                        types = p;
                else
                if (stringp(p))
                        types = ({ p });

                p=query("not_make", origin);
                if (arrayp(p))
                        types -= p;
                else
                if (stringp(p))
                        types -= ({ p });
                                                
                type = query("enchase/type", ob);
                set_temp("item/types", types);
                set_temp("item/type", type);
                set_temp("item/status", "accept2");
                set_temp("item/status", "item2_gived", me);
                set_temp("item/accept2", ob);
                
                message_vision("$N对$n说道：很好，现在可以把钱给我了！\n",
                               this_object(), me);
                remove_call_out("time_out");
                call_out("time_out", 60, me, ob);
                return 1;
        }

        if( query("money_id", ob) )
        {
                if( query_temp("item/status", me) == "answer_type" )
                {
                        message_vision("$N摇摇头，对$n说：快说你要做什么东西！\n",
                                       this_object(), me);
                        return 0;
                }

                if( query_temp("item/status", me) != "item2_gived" )
                {
                        if( query_temp("item/status", me) == "item_gived" )
                        {
                                message_vision("$N把$n递过去的" + ob->name() +
                                       "推了回来，道：你还是先给我精魂石碎片吧！\n",
                                       this_object(), me);
                                return 0;
                        }        
                        message_vision("$N把$n递过去的" + ob->name() +
                                       "推了回来，道：无功不受禄！\n",
                                       this_object(), me);
                        return 0;
                }

                if( ob->value()<query_temp("item/value", me) )
                {
                        message_vision("$N对$n说：对不起，本店开张一"
                                       "千多年来，还没有打过折扣。\n",
                                       this_object(), me);
                        return 0;
                }

                set_temp("item/money", ob);
                ob->move(this_object());

                types = query_temp("item/types");
                message_vision("$N对$n说道：好，这就给你炼！你打算打"
                               "造什么东西，请告诉我(answer 类型)！\n"
                               "（" + implode(types, "、") + "）\n",
                               this_object(), me);

                set_temp("item/status", "answer_type", me);
                return -1;
        }
        
        message_vision("莫邪眼睛一瞪，对$N说道：你给我这些东西干什么？我不要！\n", me);
        return 0;
}

int do_answer(string arg)
{
        object money;
        object ob;
        object ob2;
        object me;
        object ganjiang;
        object shi;

        me = this_player();
        if( query_temp("item/status", me) != "answer_type" )
                return 0;

        if (! arg)
                return notify_fail("你要回答什么？\n");

        message_vision("$n对$N道：就打造" + arg + "吧！\n",
                       this_object(), me);

        if (member_array(arg, query_temp("item/types")) == -1 ||
            undefinedp(item_type[arg]))
        {
                message_vision("$N“啊秋”一下打了个喷嚏，一脸无辜的看着$n。\n",
                               this_object(), me);
                return 1;
        }
        

        if( query_temp("item/type") != "all" && item_type[arg][ITEM_STYPE] != query_temp("item/type") )
        {
                message_vision("$N摇摇头，对$n说：你给我的精魂石碎片可不能用来做"+arg+"啊！\n",
                                       this_object(), me);
                return 1;
        }
        
        // 如果干将不在
        if (! objectp(ganjiang = present("gan jiang")))
        {
                message_vision("$N看了看四周，不禁一呆，说道：干将呢"
                               "？他不在，没办法做了...你改天再来吧。\n",
                               this_object());
                if (ob = query_temp("item/accept"))
                {
                        message_vision("$N把" + ob->name() + "交还给$n。\n",
                                       this_object(), me);
                        if (! ob->move(me))
                                ob->move(environment());
                }
                if (ob2 = query_temp("item/accept2"))
                {
                        message_vision("$N把" + ob2->name() + "交还给$n。\n",
                                       this_object(), me);
                        if (! ob2->move(me))
                                ob2->move(environment());
                }
                delete_temp("item");
                delete_temp("item", me);
                return 0;
        }

        if (objectp(money = query_temp("item/money")))
                destruct(money);
        delete_temp("item/money");
        set_temp("item/status", "look_working");
        set_temp("item/status", "waiting", me);
        ob = query_temp("item/accept");
        set("item/ctype", arg, ob);
        set("item/type", item_type[arg][ITEM_TYPE], ob);
        set("item/stype", item_type[arg][ITEM_STYPE], ob);
        set("item/unit", item_type[arg][ITEM_UNIT], ob);
        set("item/point",query("power_point", ob)*item_type[arg][ITEM_POINT]/100, ob);
        set("item/owner", me, ob);
        set("item/owner_id",query("id", me), ob);
        set("item/owner_name", me->name(1), ob);
        set("item/wscale", item_type[arg][ITEM_WEIGHT], ob);
        set("item/prop", item_type[arg][ITEM_PROP], ob);
        
        ob2 = query_temp("item/accept2");
        if( mapp(query("enchase/apply_prop", ob2)) )
                set("item/prop2", query("enchase/apply_prop", ob2), ob);
        set("item/quality_level", query("quality_level", ob2), ob);
        
        set("item/material_name", query("material_name", ob), ob);
        set("item/material_attrib", query("material_attrib", ob), ob);
        set("item/material_file", base_name(ob), ob);
        
        message_vision("$N把" + ob->name() + "和"+ob2->name()+"交给了$n。\n", this_object(), ganjiang);
        
        if (! ob->move(ganjiang))
                error("Can move the object to ganjiang.");
        destruct(ob2);
        remove_call_out("time_out");
        ganjiang->accept_object(this_object(), ob);
        return 1;
}

void time_out(object me, object ob)
{
        object money;
        int at_present;

        money = query_temp("item/money");

        if (! objectp(me))
                me = find_player(query_temp("item/player_id"));

        if (! objectp(me) || environment(me) != environment())
        {
                command("say 奇怪，刚才那位客人呢？怎么这就走了？\n");
                at_present = 0;
        } else
        {
                command("say 你慢慢犹豫吧，我可不能跟你耗着！想好再来吧！");
                at_present = 1;
        }

        if (money)
        {
                if (at_present)
                        command("give "+query("id", money)+
                                  " to "+query("id", me));

                if (environment(money) == this_object())
                        command("drop "+query("id", money));
        }
        ob = query_temp("item/accept");
        if (ob)
        {
                if (at_present)
                        command("give "+query("id", ob)+
                                  " to "+query("id", me));

                if (environment(ob) == this_object())
                        command("drop "+query("id", ob));
        }
        ob = query_temp("item/accept2");
        if (ob)
        {
                if (at_present)
                        command("give "+query("id", ob)+
                                  " to "+query("id", me));

                if (environment(ob) == this_object())
                        command("drop "+query("id", ob));
        }
        
        delete_temp("item");
        if (objectp(me))
                delete_temp("item", me);

}
