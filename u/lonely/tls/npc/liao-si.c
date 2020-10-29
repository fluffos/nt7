inherit F_MASTER;
inherit NPC;
string ask_me();
void create()
{
        set_name("了思禅师", ({ "liaosi chanshi","liaosi","chanshi"}) );
        set("nickname", "宿命尊者");
        set("long", "了思禅师是本观大师的弟子，他在同辈弟子\n"+
		"中最擅佛学。现司职雨花院经楼。\n");
        set("gender", "男性" );
        set("attitude", "friendly");
        set("class", "bonze");
        set("age", 53);
        set("shen_type", 1);
        set("str", 22);
        set("int", 24);
        set("con", 24);
        set("dex", 22);
        create_family("天龙寺", 14, "弟子");

        set("qi", 1300);
        set("max_qi", 1300);
        set("jing", 1200);
        set("max_jing", 1200);
        set("neili", 1600);
        set("max_neili", 1600);
        set("jiali", 50);
        set("combat_exp", 700000);
        set("score", 7000);

        set_skill("force", 90);
        set_skill("qiantian-yiyang", 90);
        set_skill("dodge", 90);
        set_skill("tianlong-xiang", 90);
        set_skill("parry", 90);
        set_skill("staff", 90);
        set_skill("finger", 90);
        set_skill("yiyang-zhi", 90);
        set_skill("buddhism", 120);
	set_skill("literate", 100);
	map_skill("force", "qiantian-yiyang");
	map_skill("dodge", "tianlong-xiang");
	map_skill("parry", "yiyang-zhi");
	map_skill("staff", "yiyang-zhi");
	map_skill("finger", "yiyang-zhi");
	prepare_skill("finger","yiyang-zhi");           
	set("book_count", 5);
	set("inquiry",([
		"佛经" : (: ask_me :),    
		"经书" : (: ask_me :),
	]));
        setup();    
        carry_object(BINGQI_D("staff"))->wield();
        carry_object("/d/tls/obj/jiasha1")->wear();
        carry_object("/d/tls/obj/sengxie")->wear();
}
string ask_me()
{
	mapping fam; 
	object ob;
	
	if (!(fam = this_player()->query("family")) || fam["family_name"] != "天龙寺")
		return RANK_D->query_respect(this_player()) + 
		"与本派素无来往，不知此话从何谈起？";
	
	if (this_player()->query_temp("tl_book"))
		return "你不是领过了吗？读经书贵精不在多，你先把那本看完吧";
	if (query("book_count") < 1)
        return "你来晚了，佛经发完了。";
	add("book_count", -1);
	this_player()->set_temp("tl_book",1);
    ob = new("/d/tls/obj/fojing2"+random(2));
	ob->move(this_player());
	return "好吧，这本经书你拿回去好好钻研。";
}
#include "liao.h";
