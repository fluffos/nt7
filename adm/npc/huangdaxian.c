#include <ansi.h>

inherit NPC;

string *qian_type =
({
        "婚姻",
});

void create()
{
        set_name("黄大仙", ({ "huang daxian", "daxian", "huang" }) );
        set("gender", "男性" );
        set("title", "风水大师");
        set("age", 85);
        set("long","一位抽签算命的老先生。\n");
        set("shen_type", 1);
        set("combat_exp", 10000);
        set("str", 17);
        set("dex", 20);
        set("con", 17);
        set("int", 22);
        set("attitude", "peaceful");
        set_skill("dodge",20);
        set_skill("unarmed",20);

        set("inquiry", ([
                "求签" : "哈哈哈哈，你也知道老夫？求签要心诚，要不要试试(qiuqian)？",
                "解签" : "这可是有违天意的啊！罢了，老夫年事已高，时日无多，你就把签给老夫看看！",
        ]));

        setup();
        carry_object("/clone/cloth/cloth")->wear();
}

void init()
{
        add_action("do_qiuqian","qiuqian");
        add_action("do_answer","answer");
}

int do_qiuqian()
{
        object me,ob,qian;
        int i;
        string str;

        me = this_player();
        ob = this_object();

        if( !wizardp(me) && time()-query_temp("last_qiuqian", me)<1800 )
                return notify_fail("才求签不久，又想求签，你当这是游戏啊？\n");

        if (present("zhu qian",me))
                return notify_fail("你身上不是有一根签么？好好琢磨琢磨吧。\n");

        command("look "+query("id", me));
        command("consider");

        qian = new("/clone/misc/qian");
        qian->csh_qianwen();
        set("owner", query("id", me), qian);

        if (!qian->move(me))
                return notify_fail("身上带这么多东西还来求签，你当是赶集啊？\n");

        message_vision("$N将一个签筒递给$n，面色凝重的叮嘱道：『记住，心诚则灵！』\n",ob,me);
        message_vision("$N微闭双眼，默默祷告，随后捧起签筒疾摇片刻，一根签掉了出来。\n",me);
        message_vision("$N赶紧放下签筒，俯身把签拣了起来，小心翼翼的收入怀中。\n",me);

        set_temp("last_qiuqian", time(), me);
        delete_temp("have_gived", me);
        delete_temp("can_answer", me);

        return 1;
}

int do_answer(string arg)
{
        object me,ob,obj;
        int i;
        string str,document,file;
        mapping qianwen;

        me = this_player();
        ob = this_object();

        if( !query_temp("can_answer", me) )
                return notify_fail("一边去，来捣什么乱！\n");

        if( !objectp(obj=query_temp("qian", me)) )
        {
                delete_temp("can_anser", me);
                delete_temp("qian", me);
                return notify_fail("一边去，来捣什么乱！\n");
        }

        if (!arg || member_array(arg,qian_type) == -1)
        {
                str = HIC "我这里有很多种签：" NOR;
                for (i = 0;i < sizeof(qian_type);i ++)
                {
                        str += HIW + qian_type[i] + HIC;
                        if (i != sizeof(qian_type) -1)
                                str += "、";
                }
                str += "，你想求哪种签？\n";
                tell_object(me, str);
                tell_object(me, "想好了就回答我！(answer 答案)\n");
                return 1;
        }

        qianwen=query("qianwen", obj);

        file = "0000000" + qianwen["id"];
        file = file[strlen(file)-3..strlen(file)-1];
        file = "/d/city/npc/qianwen/" + file + ".txt";

        document = read_file(file) + "\n";
        tell_object(me,this_object()->name() + "口中念念有词：\n");
        command("walkby "+query("id", me));
        tell_object(me,HIM + qianwen["doc"] + "\n" + NOR);
        tell_object(me,this_object()->name() + "对你说道：" + HIW + qianwen["title"] + NOR + "乃" + HIR + qianwen["type"] + NOR + "。\n");
        str = "签文含义你好好记着！\n";
        str += HIG + document + NOR;
        tell_object(me,str);
        tell_object(me,"你求的是" + HIW + arg + NOR + "，待老夫想想！\n");
        switch (arg)
        {
                case "婚姻":
                        str = qianwen["love_fate"];
                        break;
                default:
                        command("yi");
                        command("consider");
                        message_vision("$N盯着签寻思良久，脸色愈发凝重，突然将签塞回$n手中，却是一言不发！\n",this_object(),me);
                        obj->move(me);
                        return 1;
                        break;
        }
        command("whisper "+query("id", me)+" about "+str);
        command("smile "+query("id", me));
        message_vision("$N将签还给了$n。\n",this_object(),me);
        obj->move(me);

        delete_temp("can_answer", me);
        delete_temp("qian", me);

        return 1;
}

int accept_object(object me, object ob)
{
        int i;
        mapping qianwen;
        string str,document,file;

        if( query("money_id", ob) )
        {
                if( !query_temp("have_gived", me) )
                {
                        command("say 没事给老夫钱干嘛？当老夫是叫化子么？");
                        return 0;
                }
                if( ob->value()<query_temp("have_gived", me) )
                {
                        command("say 就这点钱也来糊弄老夫？当老夫穷疯了么？");
                        return 0;
                }
                command("nod "+query("id", me));
                command("say 孺子可教也！且告知老夫你所求何事？");
                str = HIC "这签可是有很多解法：" NOR;
                for (i = 0;i < sizeof(qian_type);i ++)
                {
                        str += HIW + qian_type[i] + HIC;
                        if (i != sizeof(qian_type) -1)
                                str += "、";
                }
                str += "，你想求哪种签？\n";
                tell_object(me,str);
                tell_object(me,"想好了就告诉老夫！(answer 答案)\n");
                set_temp("can_answer", 1, me);
                delete_temp("have_gived", me);
                addn("balance", ob->value(), this_object());
                destruct(ob);
                return -1;
        }

        if( query("id", ob) != "zhu qian" )
        {
                command("say 这是什么东西？老夫要来何用？");
                return 0;
        }

        if( !mapp(qianwen=query("qianwen", ob)) || 
            query("owner", ob) != query("id", me) )
        {
                command("haha");
                command("say 你哪里拣来一根牙签，也好意思来糊弄我！");
                return 0;
        }

        if (undefinedp(qianwen["id"]) ||
            !intp(qianwen["id"]) ||
            undefinedp(qianwen["title"]) ||
            !stringp(qianwen["title"]) ||
            qianwen["title"] == "" )
        {
                command("yi");
                command("consider");
                message_vision("$N盯着签寻思良久，脸色愈发凝重，突然将签塞回$n手中，却是一言不发！\n",this_object(),me);
                ob->move(me);
                return -1;
        }

        file = "0000000" + qianwen["id"];
        file = file[strlen(file)-3..strlen(file)-1];
        file = "/d/city/npc/qianwen/" + file + ".txt";

        if (file_size(file) < 0)
        {
                command("yi");
                command("consider");
                message_vision("$N盯着签寻思良久，脸色愈发凝重，突然将签塞回$n手中，却是一言不发！\n",this_object(),me);
                ob->move(me);
                return -1;
        }

        switch (qianwen["type"])
        {
                case "上上签":
                case "下下签":
                        command("heihei");
                        tell_object(me,"这签可是非同小可，老夫本也不应泄漏天机，如果你愿意给我十两黄金，尚可考虑！\n");
                        set_temp("have_gived", 100000, me);
                        break;
                default:
                        command("say");
                        tell_object(me,"这签解答虽是容易，可找别人未必就能解正天意，若想明其究竟，你可愿意给我黄金五两？\n");
                        set_temp("have_gived", 50000, me);
                        break;
        }
        set_temp("qian", ob, me);
        return 1;
}

