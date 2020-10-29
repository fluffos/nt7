#include <ansi.h>
inherit NPC;
void create()
{
        set_name("柳若松", ({ "liu" }) );
        set("gender", "男性");
        set("title", HIG"青松"NOR);
        set("combat_exp", 500000);
	set("age",32);
        set("max_atman",  300);
        set("atman",  300);
	set("env/wimpy",90);
        set("long",
	"此人原系武当门下，江湖上颇有侠名，因沉溺名利，施计陷害丁鹏，
被丁鹏揭穿其假面后竟忍辱拜丁鹏为师，意图东山再起。\n"
	);
	set_skill("sword",100);
        set_skill("move",120);
        set_skill("parry",100); 
        set_skill("dodge", 50);
	set_skill("unarmed",50);
        set("inquiry", ([
                "圆月山庄" : "我告诉你圆月山庄的秘密，你可有好处给我？不如让我看看先。(show)",
                "秘密" : "我告诉你圆月山庄的秘密，你可有好处给我？不如让我看看先。(show)",    ]) ); 
        set("chat_chance", 5);
        set("chat_msg", ({
	name()+"神秘的说道：圆月山庄的秘密.......\n",
	name()+"道：我心里在打什么主意，用不着等我说出来，你也能猜得到的。\n"
        }) );
        setup();
	carry_object("/obj/cloth")->wear();
        carry_object( __DIR__ "obj/sword")->wield();
}

void init()
{
        object ob;
        ::init();
        add_action("do_show", "show");
}

int do_show(string arg)
 {     object mygold,room,me,obj; 
       me = this_player();
       mygold = present("gold_money", this_player());
       if(!mygold) return notify_fail("柳若松干咳两声道：这年头，只有真金白银才靠得住呀。\n");
      message_vision("\n\n$N冲着柳若松轻轻地掂了掂手中的黄金...\n",me);
       if((int)mygold->query_amount() < 50)
      		return notify_fail("\n\n柳若松满脸正色地说道：这么点金子就想套出我的秘密吗？！\n");
      message_vision("\n\n柳若松一把抓过黄金，满脸堆笑对$N道：山庄内室里有条密道，请跟我来。\n",me);
       mygold->add_amount(-50);
       room = find_object("n/moon/nroom");
       if(!objectp(room)) room=load_object("u/moon/nroom");
       message_vision(HIY"\n\n柳若松带着$N匆匆忙忙向山庄内室走去....\n\n"NOR,me);
       me->move(room);
       destruct(this_object());       
}

