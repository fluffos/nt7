#include <ansi.h>

inherit NPC;

int do_borrow(string topic);
int ask_all();

protected string *books = ({
"force",
"force2",
"medical",
"medical2",
"poison",
"poison2",
});

protected string all_msg;

protected void make_book_msg()
{
        if( !all_msg )
                all_msg = "";

        foreach(string tmp in books)
                all_msg += sprintf("    %s(%s)\n", to_chinese(tmp), tmp);
}

void create()
{
        set_name("书奴", ({ "shu nu","nu","sn" }) );

        set("class","yaowang");
        set("title",HIB"读死人不偿命"NOR);

        set("gender", "男性" );
        set("age", 13);
        set("long", "这是一位英俊的少年。\n");
        set("attitude", "peaceful");

 
        set("combat_exp", 100000);
        set("str", 67);
        set("max_jing",1200);
        set("jing",1200);
        set("max_qi",1200);
        set("qi",1200);
        set("max_neili",1200);
        set("neili",1200);
        set("jiali", 10);

        set_skill("unarmed",800);
        set_skill("dodge",800);
        set_skill("parry",800);
        set_skill("force",800);
        make_book_msg();
        set("startroom", "/d/yaowang/xiaoting");

        setup();
        set("inquiry", ([
                "借书" : (: ask_all :),
                "book" : (: ask_all :),
         ]) );

}

int do_borrow(string topic)
{
        int n;
        string file;
        object book_ob;
        object who=this_player();

        if(!who
         || (query("family/family_name", who) != "药王谷" )
        || !stringp(topic)
        || !environment()
        || (base_name(environment()) != query("startroom")) )
                return notify_fail( "你不是我们药王谷的，打听它干什么？");
                
        if( ((n = member_array(topic,books)) == -1)
        && ( (n = member_array(topic,map_array(books,(: to_chinese :)))) == -1))
                return 0;
 
        file = sprintf(__DIR__"obj/book/%s_book",books[n]);
        if(file_size(file+".c") <= 0 || !book_ob = new(file))
                return 0;

        message_vision(sprintf("$N转身从书架上拿出一本%s交给了$n。\n",book_ob->name()),
                this_object(),who);
        book_ob->move(who);

        command("say 这些书你偷偷的看吧，别拿出去让人知道了。\n");
        return 1;
}

int accept_object(object who,object ob)
{
        if(!who || !ob)
                return 0;

        if(ob->is_yaowang_book())
        {
                call_out("destruct_book",1);
                return 1;
        }
        else
                return 0;
}

void destruct_book()
{
        int i,n;
        object *inv;

        inv = all_inventory(this_object());
        if(!n = sizeof(inv))
                return;

        for(i=0;i<n;i++)
                if(inv[i]->is_yaowang_book())
                        destruct(inv[i]);
}

int ask_all()
{
        object me=this_player();
        if( query("family/family_name", me) != "药王谷" )
                return notify_fail( "你不是我们药王谷的，打听它干什么？");

        tell_object(me, sprintf("\n我这里就只有这些我自己抄写的书，高级的要有谷主的命令才好。\n%s\n", all_msg));
        add_action("do_borrow", "borrow");
        add_action("do_borrow", "jieshu");
        return 1;
}