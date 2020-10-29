// qiao-feng.c

#include <ansi.h>;
#include "gaibang.h"

inherit NPC;
inherit F_MASTER;
string ask_me();

void create()
{
        set_name("乔峰", ({"qiao feng", "feng", "qiao"}));
        set("nickname", "北乔峰");
        set("gender", "男性");
        set("age", 29);
        set("long",
"他就是丐帮第十任帮主，在江湖上与燕子坞的慕容复并称为「北乔峰，南慕容」。
他身穿一件普通的粗布褂子，腰间用一条麻绳随便一系。他身高六尺有余，体格
十分魁梧，长有一张线条粗旷、十分男性化的脸庞，双目如电，炯炯有神。\n");
        set("attitude", "peaceful");
        set("class", "beggar");
         set("beggarlvl", 10);

        set("str", 30);
        set("int", 24);
        set("con", 30);
        set("dex", 24);

        set("qi", 2500);
        set("max_qi", 2500);
        set("jing", 800);
        set("max_jing", 800);
        set("neili", 3000);
        set("max_neili", 3000);
        set("jiali", 300);

        set("combat_exp", 3000000);
        set("score", 200000);
        set("shen", 100000);

        set_skill("force", 200);             // 基本内功
        set_skill("huntian-qigong", 200);    // 混天气功
        set_skill("unarmed", 200);           // 基本拳脚
        set_skill("dodge", 200);                   // 基本躲闪
        set_skill("xiaoyaoyou", 300);        // 逍遥游
        set_skill("parry", 200);             // 基本招架
        set_skill("strike", 200);            // 基本掌法
        set_skill("dragon-strike", 300);   // 降龙十八掌
        set_skill("hand", 200);              // 基本手法
        set_skill("suohou-hand", 300);       // 锁喉擒拿手
        set_skill("blade", 200);             // 基本刀法
        set_skill("liuhe-dao", 300);       // 四象六合刀
        set_skill("staff", 200);             // 基本杖法
        set_skill("fengmo-zhang", 300);      // 疯魔杖法
        set_skill("stick", 200);             // 基本棒法
        set_skill("dagou-bang", 300);        // 打狗棒法
        set_skill("begging", 100);           // 叫化绝活
        set_skill("checking", 100);          // 道听途说
        set_skill("training", 100);          // 驭兽术
        set_skill("lianhua-zhang",85); // 莲花掌

        map_skill("force", "huntian-qigong");
        map_skill("strike", "dragon-strike");
        map_skill("hand",  "suohou-hand");
        map_skill("dodge", "xiaoyaoyou");
        map_skill("blade", "liuhe-dao");
        map_skill("parry", "dagou-bang");
        map_skill("stick", "dagou-bang");
        map_skill("staff", "fengmo-zhang");
//        prepare_skill("hand",  "suohou-hand");
        prepare_skill("strike", "dragon-strike");

        set("inquiry",([
                "秘籍"     : (: ask_me :),
                "棒法入门" : (: ask_me :),
        ]));
        set("book_count", 1);
        //set("party/party_name", HIC"丐帮"NOR);
        //set("party/rank", HIR"帮主"NOR);
        //set("party/level", 10);
        create_family("丐帮", 10, "帮主");

        setup();

        carry_object(__DIR__"obj/lvyv_bang")->wield();
        carry_object(__DIR__"obj/cloth")->wear();
//      carry_object(BOOK_DIR"stick_book")->wear();
}

void attempt_apprentice(object ob)
{
        string title=query("title", ob);
        int lvl=query("family/beggarlvl", ob);

        command("sigh");
        command("say 走开，我不收徒。");
        return;

        if (! permit_recruit(ob))
                return;

        if( query("combat_exp", ob)<200000 )
        {
                command("say 你的江湖经验不够，还是先向各位长老学习吧。");
                return;
        }

        if( query("shen", ob)<30000 )
        {
                command("say 你身为丐帮弟子，竟然不做好事？");
                return;
        }

        if( query("family/beggarlvl", ob)<5 )
        {
                command("say 你在本帮的地位太低，还是先向各位长老学习吧。");
                return;
        }

        if ((int)ob->query_str() < 26)
        {
                command("say 我的武艺以刚猛为主，你膂力不行，还是算了吧。");
                return;
        }

        if (ob->query_skill("force") < 150)
        {
                command("say 你的内功火候还不够，还是先向各位长老学习吧。");
                return;
        }
        command("nod");
        command("say 我今日便收你为徒，倘若勤恳努力，将来必有一番作为。");
        command("recruit "+query("id", ob));

        if( query("class", ob) != "beggar" )
                set("class", "beggar", ob);

        if (lvl > 0)
        {
                set("family/beggarlvl", lvl, ob);
                set("title", title, ob);
        }
}

string ask_me()
{
        mapping fam;
        object ob;

        if( !(fam=query("family", this_player())) || 
                fam["family_name"] != "丐帮")
                return RANK_D->query_respect(this_player()) +"与本派毫无瓜葛，我派的武功典籍可不能交给你。";
        if (query("book_count") < 1)
                return "你来晚了，本派的秘籍不在此处。";
        addn("book_count", -1);
        ob = new("/clone/book/stick_book.c");
        ob->move(this_player());
        command("rumor"+query("name", this_player())+"拿到棒法入门啦。\n");
        return "好吧，这本「棒法入门」你拿回去好好钻研。";
}
