// zhang.c 张天师

#include <ansi.h>

inherit KNOWER;

#define ZHOUTIAN_D      "/adm/daemons/zhoutiand"

int ask_me();
string ask_fu();
int life_warcraft();
string ask_tianjidao();

void create()
{
        set_name("张天师", ({ "zhang tianshi", "zhang" }));
        set("age", 57);
        set("gender", "男性");
        set("long", "这是一位仙风神骨，道貌岸然的法师。\n");
        set("attitude", "peaceful");

        set("str", 28);
        set("int", 35);
        set("con", 38);
        set("dex", 31);

        set("max_qi", 8000);
        set("max_jing", 8000);
        set("max_neili", 8000);

        set_skill("magic", 200);
        set_skill("taoism", 350);

        set("chat_chance_combat", 3);
        set("chat_msg_combat", ({
                "张天师摇摇铃铛，道：天灵灵，地零零，太上老君还不显灵？\n",
                "张天师呼呼的吹了几口气。\n",
        }));

        set("inquiry", ([
                "开光" : (: ask_me :),
                "魔兽复活": (: life_warcraft :),
                "没钱" : "没钱就去赚，跟我说什么。",
                "穷"   : "看你也是一副穷命。",
                "魔法" : "魔法？什么玩艺？",
                "法术" : "法术还分很多种呢，道术、妖术、仙术不一而足。",
                "道术" : "道术？这可是本源正宗！",
                "妖术" : "妖术啊，趋于下乘，不足为提。",
                "仙术" : "仙术只好算是中乘，还是不能和道术相比。",
                "浸入" : "你要是不行我可以帮你看看(show)浸入需要用什么物品。",
                "鉴定" : "我可以帮你看看(show)你的宝石都蕴涵哪些属性。",
                "赛神龙" : "呵呵，那是贫道的一位故友，现在也不知他生死如何了。",
                "万年红" : "此乃天下间最上乘的颜料，画符首选，可用碧血石+火龙果+乾坤圣水合成。",     
                "童男童女符" : (: ask_fu :),
                "天极道" : (: ask_tianjidao :),
        ]));

        setup();
        carry_object("/clone/cloth/dao-cloth")->wear();
}

string ask_fu()
{
        object me;
        object ob_wnh,ob_zz;
        object ob_fu;
        
        me = this_player();

        command("say 童男童女符乃贫道为昔日故友所造，如果阁下需要的话贫道到是可以效劳。");
        command("say 不过，还需要以下一些材料：首先是万年红，此乃宫廷禁品，天下间最上乘的颜料。");
        command("say 其次，天然珍珠，用天然珍珠粉末与万年红调和，可使画出的符效果最佳。");
        command("say 最后，当然，贫道也需要收取一些制作费，总共需要10万两黄金。");
        command("ke");
        command("say 怎么样，如果以上材料都找齐了可以来找我，我会制作出童男童女符给你，此符下线不丢失。");
        
        // 需要万年红
        if (! objectp(ob_wnh = present("wannian hong", me)))
                return "你好象还没备齐万年红颜料吧？\n";        
                                
        if (base_name(ob_wnh) != "/clone/fam/item/wannian-hong")
                return "你好象还没备齐万年红颜料吧？\n";
                
        // 需要天然珍珠 
        if (! objectp(ob_zz = present("tianran zhenzhu", me)))
                return "你好象还没备齐天然珍珠吧？\n";          
                        
        if (base_name(ob_zz) != "/clone/quarry/item/zhenzhu")
                return "你好象还没备齐天然珍珠吧？\n";          
        
        // 需要黄金一万两
        if (query("balance", me) < 1000000000)
                return "你好象没有备齐10万两黄金吧。\n";
                
        // 物品已经备齐
        destruct(ob_wnh);
        destruct(ob_zz);
        addn("balance", -1000000000, me);
        
        ob_fu = new("/clone/fam/item/tntn_fu");
        
        command("say 不错，既然我要的东西你都备齐了，我这就将童男童女符给你。");
        
        message_sort("\n" HIC "$N" HIC "将万年红和天然珍珠粉末混合在一起，拿出一张黄色的道符，然后口中"
                     "默念符咒，一柱香的时间，一张童男童女符已经画好。\n" NOR, this_object());

        ob_fu->move(me, 1);
        
        message_vision("$N" NOR "拿出" + ob_fu->name() + NOR "给$n" NOR "。\n" NOR, this_object(), me);

        return "这符我也做好了，钱也收了，从此我们两不相欠。\n";                
}

void init()
{
        add_action("do_show", "show");
        add_action("do_summon", "summon");
}

int life_warcraft()
{
        object me, ob;
        
        me = this_player();
        
        if( !query("warcraft/file", me) ) 
        {
                command("say 你目前没有魔兽，请到扬州找狂风购买，详情见 help warcraft。");
                return 1;
        }

        if( query("warcraft/status", me) != "died" )
        {
                command("shake");
                command("say 你的魔兽目前并没有死亡啊。");
                return 1;
        }
        if( !query_temp("want_life_warcraft", me) )
        {
                command("hehe");
                command("say 既然如此，那你就交五千两黄金吧，贫道变给你作一次法。");
                command("say 如果你确认银行中有足够黄金，那么请再输入一次该指令。");
                
                set_temp("want_life_warcraft", 1, me);
                
                return 1;
        }
        
        if( query("balance", me) < 50000000)
        {
                command("heng");
                command("say 说好五千两黄金，难道你想戏耍贫道！！！");
                return 1;
        }
        
        addn("balance", -50000000, me);
        
        message_vision(HIM "$N" HIM "拿出一张符，点燃了抛向空中，然后念着：#￥%……·￥·…·#￥...\n" NOR, this_object());
        
        set("warcraft/status", "living", me);

        command("say 好了，你的魔兽复活了，使用 whistle <id> 就可以召唤出来了。");
        
        delete_temp("want_life_warcraft", me);
        me->save();

        return 1;
        
}
int ask_me()
{
        command("heihei");
        command("say 我只给神兵利器开光，寻常刀剑莫提！要"
                "你本人的，我可不能帮你做坏事！");
        tell_object(this_player(), GRN "张天师在你耳边悄悄说："
                    "你把要开光的拿出来给我看看(show)！\n" NOR);
        return 1;
}

int do_summon(string arg)
{
        if (! wizardp(this_player()))
        {
                command("say 你在我面前瞎抓个什么劲？别地试去！");
                return 1;
        }

        return 0;
}

int do_show(string arg)
{
        object money;
        object ob;
        mixed  obj;
        object me;
        string fn, filename;
        int    n, d;

        if (! arg)
                return notify_fail("你要亮出什么东西？\n");

        me = this_player();
        if (! objectp(ob = present(arg, me)))
                return notify_fail("你身上没有这种东西。\n");

        if( query("equipped", ob) )
                return notify_fail("你先解除" + ob->name() + "的装备再说！\n");

        message_vision("$n拿出一"+query("unit", ob)+ob->name()+
                       "对$N说：“拜托拜托...”\n",
                       this_object(), me);

        if( query("money_id", ob) )
        {
                command("say 你亮出钱干什么？想献给观里？那就给我好了。");
                return 1;
        }

        if( !wizardp(me) && !query_temp("zhangpaid/张天师", me) )
        {
                command("heihei");
                command("say 这...怎么也的有点意思意思吧？你"
                        "说十两黄金怎么样？当然多些我也不反对。");
                return 1;
        }

        if( ob->query_tongren() && query("no_identify", ob) )
        {
                if (! objectp(obj = ZHOUTIAN_D->identify_tongren(me, ob)))
                {
                        command("say 你的物品乃我所从未见过，叫巫师来处理吧。");
                        return 1;
                }
                obj->move(me, 1);
                command("say 行了，你的冲穴铜人我给鉴定完了，拿去吧。");
                delete_temp("zhangpaid/张天师", me);
                return 1;
        }

        if( ob->is_tessera() && query("no_identify", ob) )
        {
                if (! objectp(obj = IDENTIFY_D->identify_ob(me, ob)))
                {
                        command("say 你的物品乃我所从未见过，叫巫师来处理吧。");
                        return 1;
                }
                message("vision", sort_string(HIM + name() + "从口袋中摸出一张黄色"
                                "的符纸，抽出背后的桃木剑，将那符纸点燃了，盖在" +
                                ob->name() + HIM "上，然后口中念念有词：“太上老君"
                                "急急如律赐令！”说罢一抖掌中剑，喝道：“疾”！\n" NOR, 64),
                                environment());
                tell_object(me, HIC "你感受" + ob->name() + HIC"发生了不可言喻的变化。\n" NOR);

                destruct(ob);
                obj->move(me, 1);
                delete("no_identify", obj);
                command("say 行了，你的宝物我给鉴定完了，拿去吧。");
                delete_temp("zhangpaid/张天师", me);
                return 1;
        }

        if( stringp(query("magic/imbue_ob", ob)) )
        {
                command("say 嗯...我看看，应该用" +
                        query("magic/imbue_ob", ob)->name()+
                        CYN "浸入它才能进一步激发它的潜力。" NOR);
                delete_temp("zhangpaid/张天师", me);
                return 1;
        }

        if( mapp(query("magic/imbue_ok", ob)) )
        {
                command("say 哦！我看它现在已经不需要在浸入了，"
                        "要发挥潜力得用别的法子了。\n");
                return 1;
        }

        if (! ob->is_item_make())
        {
                command("heng");
                command("say 这...这...我看还是算了吧！");
                return 1;
        }

        if( ob->item_owner() != query("id", me) )
        {
                command("kick"+query("id", me));
                command("say 你以为本山人的仙术是蒙事的啊，这分明不是你的！");
                return 1;
        }

        if( query("can_summon/"+query("id", ob), me) )
        {
                if (ob->weapon_level() > 1)
                {
                        command("poor"+query("id", me));
                        command("say 它现在还不到浸入的时候..."
                                "你要先圣化它才行啊！");
                } else
                {
                        command("kok"+query("id", me));
                        command("say 你和它已经有缘了！我说你的"
                                "记性怎么这么差？");
                }
                return 1;
        }

        message("vision", sort_string(HIM + name() + "从口袋中摸出一张黄色"
                                "的符纸，抽出背后的桃木剑，"
                                "将那符纸点燃了，扫过" + ob->name() + HIM "，然"
                                "后用桃木剑穿了，手舞足蹈，口中念念有词："
                                "“太上老君急急如律赐令！”说罢一抖掌中剑，"
                                "喝道：“疾”！\n" NOR, 64), environment());
        message_vision("焰光划出一道光华，$N发了发呆，也不知道算是怎么回事。\n",
                       me);
        command("say 行了，行了！你可以走了。");
        delete_temp("zhangpaid/张天师", me);
        set("can_summon/"+query("id", ob), base_name(ob), me);
        MYGIFT_D->check_mygift(this_player(), "newbie_mygift/kaiguang");
        log_file("static/item", sprintf("%s %s sancitfy %s(%s)\n",
                        log_time(), log_id(me),
                        filter_color(ob->name(1)),query("id", ob)));
        return 1;
}

int accept_object(object who, object ob)
{
        if( !query("money_id", ob) )
        {
                command("say 这玩艺我可没啥兴趣！");
                return 0;
        }

        if (ob->value() < 50000)
        {
                command("say 算是给观里的香火么？那我就收下了！");
                return 1;
        }

        if (ob->value() < 100000)
        {
                command("say 唉！看你也算有点心意，我就替你开一次光吧！");
                set_temp("zhangpaid/张天师", 1, who);
                destruct(ob);
                return 1;
        }

        command("say 好...好...这么照顾本观，我能帮你点什么？");
        set_temp("zhangpaid/张天师", 1, who);
        destruct(ob);
        return 1;
}

void fight_ob(object ob)
{
        ::fight_ob(ob);
        message_vision("$N冷笑一声，道：“这年头，什么人都有。”说完伸手一指$n。\n",
                       this_object(), ob);
        ob->unconcious();
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

void receive_damage(string type, int n)
{
        return;
}

void receive_wound(string type, int n)
{
        return;
}

string ask_tianjidao()
{
        object *obs;
        object ob;
        object me;
        object ob_hlp;
        int i;
        
        me = this_player();
        
        if( query("int", me)<32 || 
            query("con", me)<32 || 
            query("str", me)<32 || 
            query("dex", me)<32 )
            return "你的先天属性还不足以修炼天极道，我看你还是先回去吧。\n";


        if( query("reborn/times", me)<3 )
                return "走开，走开，没看我正忙吗？\n";
        
        if( me->query_skill("yinyang-shiertian",1) && query("reborn/times", me)<4 )
                return "阁下武功已经独步天下，何必如此贪心?\n";

        if (me->query_skill("lunhui-sword",1))
                return "哼，凡夫俗子，竟然如此贪心！\n";
                                        
        // 已经完成任务
        if( query("lunhui-sword_quest/tianjidao/finish", me) )
                return "呵呵，不错不错，上次那些天蚕丝解了老夫燃眉之急啊。\n";

        // 分配任务
        if( !query("lunhui-sword_quest/tianjidao/give_quest", me) )
        {
                command("shake");
                command("say 不久前，老夫将借来的一件天蚕宝甲给弄丢了，不知如何是好？");
                command("say 如果能搜集到30根天蚕丝，老夫倒是有办法重新制作一。");
                command("不过……");
                command("tan");
                command("say 那天蚕丝并非凡物，只有天山顶峰的天蚕身才有，看来这次真是闯大祸了！");
                command("look"+query("id", me));
                command("say 阁下如果能搜集到30根天蚕丝给老夫，老夫这里倒是有一些厉害的武功可以传授给你。");
                tell_object(me, this_object()->name() + HIG "让你帮他搜集30根天蚕丝，赶快去吧！\n" NOR);
                set("lunhui-sword_quest/tianjidao/give_quest", 1, me);
                me->save();
                return "怎么样，考虑考虑？";
        }
        
        // 完成任务
        
        if (! objectp(ob_hlp = present("tiancan si", me)))
                return "怎么样，30根天蚕丝搜集够了吗？\n";
                
        if (base_name(ob_hlp) != "/clone/quarry/item/cansi2")
                return "怎么样，30根天蚕丝搜集够了吗？\n";
                
        obs = all_inventory(me);
        obs = filter_array(obs, (: base_name($1) == "/clone/quarry/item/cansi2" :));
        if( sizeof(obs) < 30 )
                return "怎么样，30根天蚕丝搜集够了吗？\n";
                
        for (i = 0; i < 30; i++)
        {
                ob = obs[i];
                obs[i] = 0;
                destruct(ob);
        }
        
        command("hehe");
        command("nod");
        command("say 既然你帮我了这个忙，好！老夫也遵守诺言，传你「天极道」……");
        
        message_sort(HIC "\n$N" HIC "走上前去，在$n" HIC "耳边悄悄说了几句，然后又拿出一本书，指指点点，"
                     "$n" HIC "不住地点头，忽而眉头深锁，忽而低头沉思 ……\n良久，$n" HIC "大笑一声，似乎"
                     "对刚才的疑虑有所顿悟。\n", this_object(), me);
                        
        tell_object(me, HIG "恭喜你领悟了「天极道」剑法，目前等级为10级。\n");
        me->set_skill("tianji-dao", 10);
        set("lunhui-sword_quest/tianjidao/finish", 1, me);
        
        return "多谢了！";
        
                
}
