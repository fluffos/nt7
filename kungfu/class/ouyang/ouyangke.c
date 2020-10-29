// ouyangke.c

#include <ansi.h>
#include "ouyang.h"

inherit F_MASTER;
inherit NPC;

void greeting(object ob);
int  accept_object(object who, object ob);
void do_back();
string ask_shenshe(string name);
string ask_job();
void reward_dest(object obj,object ob);
void destroy_dest(object obj,object ob);
void destroy_staff(object obj,object ob);
void thank_dest(object obj,object ob);

void create()
{
        seteuid(getuid());
        set_name("欧阳克", ({ "ouyang ke", "ouyang", "ke" }));
        set("long", "他一身飘逸的白色长衫，手摇折扇，风流儒雅。\n");
        set("title", "欧阳世家少庄主");
        set("nickname", "玉面蛇心");
        set("gender", "男性");
        set("age", 27);
        set("attitude", "friendly");
        set("shen_type", -1);

        set("str", 25);
        set("int", 29);
        set("con", 25);
        set("dex", 26);

        set("qi", 1700);
        set("max_qi", 1700);
        set("jing", 800);
        set("max_jing", 800);
        set("neili", 3000);
        set("max_neili", 3000);
        set("jiali", 50);

        set("combat_exp", 300000);

        set_skill("cuff",  130);
        set_skill("dodge", 120);
        set_skill("parry", 140);
        set_skill("force", 130);
        set_skill("staff", 100);
        set_skill("training", 80);
        set_skill("hamagong",130);
        set_skill("chanchu-bufa", 120);
        set_skill("lingshe-quan", 130);
        set_skill("baibian-daxue", 120);
        set_skill("poison", 120);
        set_skill("finger", 100);
        set_skill("shedu-qiqiao", 120);
        set_skill("medical", 150);
        set_skill("baituo-michuan", 150);
        set_skill("literate", 150);

        map_skill("force", "hamagong");
        map_skill("dodge", "chanchu-bufa");
        map_skill("cuff",  "lingshe-quan");
        map_skill("parry", "baibian-daxue");
        map_skill("staff", "baibian-daxue");
        map_skill("shedu-qiqiao", "shedu-qiqiao");
        map_skill("finger", "shedu-qiqiao");

        prepare_skill("finger", "shedu-qiqiao");
        prepare_skill("cuff", "lingshe-quan");

        create_family("欧阳世家", 6, "传人");

        set("inquiry", ([
                "引路神蛇"   : (: ask_shenshe, "shenshe" :),
                "欧阳峰" : "他是我叔父。",
                "化尸粉" : "我只有一份化尸粉，不能给你。不过你要是给我一具尸体，我可以给你做些。",
                "活" : (: ask_job :),
                "job" : (: ask_job :),
        ]));

        set("chat_chance", 2);
        set("chat_msg", ({
                "欧阳克唱道：漂亮姑娘你请留步￣￣让我多看你一眼￣￣\n",
                "欧阳克色迷迷地看着街边的小姑娘。\n",
                "欧阳克把纸扇一展，转过身去，深情地吟道：红颜知己最难得￣\n",
        }) );

        set("master_ob",3);
        setup();
        carry_object("/d/baituo/obj/baipao")->wear();
        add_money("silver",10);
}

void init()
{
        object ob;

        ::init();

        if( interactive(ob = this_player()) && !is_fighting() )
        {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
}

void greeting(object ob)
{
        if (!ob || environment(ob) != environment()) return;

        if (check_family(ob, "欧阳世家"))
        {
                command("nod"+query("id", ob));
                return;
        }

        if( query("gender", ob) == "女性" )
        {
                if( query("per", ob)<22 )
                        return;

                if( query("sex/欧阳克", ob) )
                {
                        command("kiss"+query("id", ob));
                        command("say 怎么样，要不要再来几次啊... 嘻嘻。");
                } else
                switch(random(3))
                {
                case 0: command("rose "+(string)query("id", ob));break;
                case 1: command("kiss "+(string)query("id", ob));break;
                case 2: command("love "+(string)query("id", ob));break;
                }

        }
        else
                say("欧阳克叹了一口气说：这位"+RANK_D->query_respect(ob)+
                        "，你要是能给我弄一个女人来就好了。\n");
        return;
}

void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob))
                return;

        message_vision("$N道：好... 很好！\n", this_object());
        command("recruit "+query("id", ob));
        if( !query("special/shenshe", ob) )
        {
                command("say 你还不会使用引路神蛇吧？我告诉你口诀，你可不要忘记了！");
                command("whisper"+query("id", ob)+"口诀是：@#$%^&*，你"
                        "拿着引路神蛇到了西域沙漠就可以让神蛇带你回家了！");
                set("special/shenshe", 1, ob);
        }
}

int accept_fight(object ob)
{
        if( query("gender", ob) == "女性" )
        {
                message_vision("欧阳克摆摆手说道：这位"+RANK_D->query_respect(ob)+
                "，我怎能欺负女孩子呢！\n", ob);
                return 0;
        }

        return ::accept_fight(ob);
}

void do_back()
{
        remove_call_out("do_back");
        if (base_name(environment()) == query("startroom"))
                return;

        if (! living(this_object()) ||
            is_busy() || is_fighting())
        {
                call_out("do_back", 10 + random(10));
                return;
        }

        message_vision("$N轻摇羽扇，飘然而去。\n", this_object());
        move(query("startroom"));
        message_vision("$N轻摇羽扇，施施然的走了过来。\n", this_object());
}

string ask_shenshe(string name)
{
        mapping fam;
        object ob;

        if( !(fam=query("family", this_player())) || fam["family_name"] != "欧阳世家" )
                return RANK_D->query_respect(this_player()) +
                "，你并不是本山庄的人，此话从何说起？";

        if (  present("shen she", this_player()) )
                return RANK_D->query_respect(this_player()) +
                "你身上不是有神蛇吗？怎么又来要？真是贪得无厌！";

        ob = new("/d/baituo/obj/" + name);
        ob->move(this_player());

        message_vision("欧阳克给$N一条"+query("name", ob)+"。\n",this_player());
        return "此神蛇乃本山庄特有，切记不可给予他人！";
}

string ask_job()
{
        mapping job_stat;
        object ob2;
        object ob = this_player();
        object me = this_object();
        object guaishe,staff,here=environment(me);
                string dataname;
        int good_skill;

                dataname=query("id", ob);

        job_stat=query_temp("baituo/feeding", ob);

        if( query("family/family_name", ob) != "欧阳世家" )
                return RANK_D->query_rude(ob)+"莫非别有用心！\n";

        if( query_temp(dataname, me)>5 )
                       return "你已经跟我要了五只蛇了都还没还给我，我现在不放心给你蛇，你去冷静一下吧。\n";


        if( ob->is_busy() ){
                command("hmm"+query("id", ob));
                return "你还在忙着干别的事呢！\n";
        }

        if( job_stat ){
                command("hmm"+query("id", ob));
                return "你还没干完活呢!\n";
        }

        if( ob->query_skill("training") < 10 && random(4)!=0 ) {
                return "你的驯兽术太低，随便拿只蛇练练去吧。\n";
        }

        ob->start_busy(random(4));
        good_skill=to_int(pow(to_float(query("combat_exp", ob)/100),1.0/3))*10*0.7*3/2;

        if( query("combat_exp", ob)>20000 && (ob->query_skill("force")<good_skill) && random(15)>0){
                command("say 你去好好练习一下蛤蟆功吧！");
                return "蛤蟆功是本派的独门绝技，练成之后一定可以帮本少爷多抓几个美女来！\n";
                }

        if( query("combat_exp", ob)>5000 && 
        query("max_neili", ob)<ob->query_skill("force")*7 && random(5)>0){
                command("say 你内力不够，去好好打坐一下吧！");
                return "内力越高，蛤蟆功的威力就越大，嘿黑，和美眉在一起也。。。\n";
                }



        if( query_temp("job_pos", me) == 0){
                if(random(8)==1)
                set_temp("job_pos", 1, me);
                return "现在没什么事，你自个儿晃荡去吧。\n";
        }

        addn_temp("job_pos", -1, me);
                addn_temp(dataname, 1, me);

        command("nod");
        command("say好，我这里有一只奇毒的怪蛇，"+query("name", ob)+"你拿去好好调养。");
        command("say 这怪蛇吃鸟类、吸人血。越是所谓名门正派的高手的气血越是滋养怪蛇。");
        command("hehe");
        command("say 它吃饱了以后，就会乖乖的爬进蛇杖里成为天下最厉害的兵器。");


        guaishe = present("guai she",me );
        if(guaishe)destruct(guaishe);
        guaishe = present("guai she",me );
        if(guaishe)destruct(guaishe);
        ob2 = new("/d/baituo/npc/guaishe");
        ob2->move(me);
        ob2->set_owner(ob);
        set_temp("baituo/feeding", 1, ob);
        addn("bt/job", 1, ob);
        set("bt/time", time(), ob);
        command("giveguaisheto"+query("id", ob));
        guaishe = present("guai she",me );
        if(guaishe)command("drop guai she");

        staff = present("guai shezhang",here);
        if(!staff)staff=present("guai shezhang",ob);
        if(staff)destruct(staff);
        staff = new("/clone/weapon/gshezhan");
        staff->move(me);
        command("giveguaishezhangto"+query("id", ob));
        guaishe = present("guai shezhang",me );
        if(guaishe)command("drop guai shezhang");

        return "千万别弄丢了！\n";
}

int accept_object(object me, object obj)
{
        object obn;
        int addition;
        object hsf, ob = this_player();

        if( query("id", obj) == "corpse" )
        {
                if( !query("family", me) || query("family/family_name", me) != "欧阳世家"){
                        command("say 你要我给你收尸不成？\n");
                        return 0;
                }
                if( query("family/master_name", me) != "欧阳锋" && 
                        query("family/master_name", me) != "欧阳克"){
                        command("say 你还是先练好功夫吧。\n");
                        return 0;
                }

                if( query_temp("huashifen", me)){
                         command("say 化尸粉这样烈性的药物不要用得过多。\n");
                        return 0;
                 }

                message_vision("$N将" + obj->name() + "放在地上，从怀中掏出一份化尸粉撒在上面。\n",this_object());
                message_vision("片刻之间，" + obj->name() + "化作一滩黄水。黄水干了后成了一堆发出荧荧的黄光的粉末。\n" ,obj);
                message_vision("$N将其中一份收在怀中，其余的交给$n。\n",this_object(),me);
                command("say 你可以把化尸粉倒在尸体上，可即刻将其融化掉。");
                command("say 你也可以把它涂在绷带上给人佯装裹伤，待毒性深入其伤口，他就死定了。");
                command("hehe ouyang ke");

                hsf = new(DRUG_D("huashi"));
                hsf->set_amount(10);
                hsf->move(me);
                set_temp("huashifen", 1, me);
                return 1;
        }

        command( "say "+obj->name()+"?");

        if( query("id", obj) == "guaishe"){
                call_out("destroy_dest", 1, obj, ob);
                return 1;
        }

        if( query("id", obj) == "guaishezhang"){
                if( query("family/family_name", ob) == "欧阳世家"){
                        if( query("snake", obj)>0 )
                                call_out("reward_dest", 1, obj, ob);
                        else
                                call_out("destroy_staff", 1, obj, ob);
                }
                else {
                        call_out("thank_dest", 1, obj, ob);
                }
                return 1;
        }

        if( !obj->is_character() || query("gender", obj) != "女性" )
        {
                      command("say 我欧阳克不需要这件东西。");
                return 0;
        }

        if( query("born_family", obj) == "欧阳世家" )
        {
                command("kick"+query("id", me));
                command("slap"+query("id", me));
                command("say 我靠：你胆子可真不小，连我的胞妹你也敢欺负？");
                return 1;
        }

        if( query("short", environment(this_object())) == "丽春院" )
        {
                       command("say 我已经有女人了，你改天再送来吧。");
                return 0;
        }

        if( query("age", obj)<18 )
        {
                command("fear");
                command("say 未成年少女我怎敢要！");
                return 0;
        }

        if( query("age", obj)>29 )
        {
                command("say 这种老古董还是留给你自己吧！");
                return 0;
        }

        addition = 0;
        addition+=query("per", ob);
        if (userp(obj))
        {
                command("papapa");
                command("say 靠，你小子怎么比我还色，这个女的还是你自己留着吧！");
                return 0;
        }

        if( query("sex/欧阳克", obj) >= 3 )
        {
                command("shake");
                command("say 这女人我已经玩腻了，你自个留着吧。");
                return 0;
        }

        if( !query("sex", ob) )
        {
                command("say 哇，这还是个处女，怎么也得多给"
                        "你点辛苦费！");
                addition += 30;
        }

        obn=new("/clone/money/silver");
        obn->set_amount(20 + addition);
        obn->move(me);

        message_vision("$n把" + obj->name() + "交给了$N。\n",
                       this_object(), me);

        message_vision("$N一把把" + obj->name() + "揽在怀里，对$n说："
                       "这点银子是你的辛苦费，咱回头见。\n说完，就携着" +
                       obj->name() + "往丽春院奔去...\n",
                       this_object(), me);

        obj->move("/d/city/lichunyuan");
        move("/d/city/lichunyuan");

        message_vision("$N抱着昏迷不醒的$n走了进来。\n", this_object(), obj);

        addn("sex/欧阳克", 1, obj);
        addn("sex/times", 1, obj);
        if( query("sex/times", obj) == 1 )
                set("sex/first", "欧阳克", obj);

        obj->revive();
        tell_object(obj, HIY "你刚刚挣开眼睛，却发现一个人"
                        "正抱着你，你大叫一声，几乎晕了过去。\n\n" NOR);
        command("kiss"+query("id", obj));
        command("say 嘻嘻，你慌什么么嘛，可是" + me->name() +
                "把你送过来的啊。");
        /*
        shout(sprintf(HIW "\n%s(%s)大声喊道：救命啊... 救... 救命...\n\n" NOR,
                      obj->name()+HIW,query("id", obj)));
        */

        if (! userp(obj))
        {
                set("chat_chance", 15, obj);
                obj->set("chat_msg",({
                        obj->name() + "不住的抽泣。\n",
                        obj->name() + "呜咽道：" + this_object()->name() + "，他... 他... 他这个坏东西。\n",
                        obj->name() + "哭了起来：我不想活了！\n",
                }) );
        }

        remove_call_out("do_back");
        call_out("do_back", 10 + random(10));
        return -1;
}

void reward_dest(object obj,object ob)
{
        string dataname;

        dataname=query("id", ob);

        command("pat"+query("id", ob));
        command("say"+query("name", ob)+"干的还不错，这样多干活，将来本少爷一定会赏你的！\n");

        if( query("gender", ob) == "女性" )
                command("kiss1"+query("id", ob));

        if( query_temp("baituo/feeding", ob) )
        {
                delete_temp("baituo/feeding", ob);
                addn_temp("job_pos", 1);
        }
        addn_temp(dataname, -1, this_object());

                if( query_temp(dataname, this_object())<1 )
                {
                        delete_temp(dataname, this_object());
                }

                destruct(obj);
}


void destroy_staff(object obj,object ob)
{
        command( "hmm" );
        command("kick"+query("id", ob));
        command( "say 怎么就这样还给我？蛇呢？小心少爷我赏你一蛇杖！" );
        command( "angry" );

        destruct(obj);
}

void destroy_dest(object obj,object ob)
{
        command( "hmm" );
        command("kick"+query("id", ob));
        command( "say 怎么就这样还给我？应该喂饱变成蛇杖再交给我。小心少爷我赏你给蛇吃！" );
        command( "angry" );

        if( query_temp("baituo/feeding", ob) )
        {
                delete_temp("baituo/feeding", ob);
                addn_temp("job_pos", 1);
        }
        destruct(obj);
}


void thank_dest(object obj,object ob)
{
        command( "ah");
        command( "jump");
        command( "say 本少爷的蛇杖？多谢啦！\n");
        destruct(obj);
}


int accept_ask(object me, string topic)
{
        switch (topic)
        {
        case "历练" :
        case "历炼" :
        case "锻炼" :
                return QUEST_D->accept_ask(this_object(), me, topic);
                break;

        case "打字诀" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/shedu-qiqiao/da",
                           "name"    : "打字诀",
                           "sk1"     : "shedu-qiqiao",
                           "lv1"     : 100,
                           "sk2"     : "force",
                           "lv2"     : 100,
                           "neili"   : 2000,
                           "gongxian": 200,
                           "shen"    : -4000, ]));
                break;

        case "炼毒" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/shedu-qiqiao/liandu",
                           "name"    : "炼毒",
                           "sk1"     : "shedu-qiqiao",
                           "lv1"     : 120,
                           "sk2"     : "force",
                           "lv2"     : 120,
                           "neili"   : 2000,
                           "gongxian": 300,
                           "shen"    : -6000, ]));
                break;

        default:
                return 0;
        }
}

