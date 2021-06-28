//Edited by fandog, 02/13/2000

inherit NPC;
string ask_me();

void create ()
{
        object weapon;
        set_name("狄云", ({"di yun","di"}));
        set("long", "他长脸黝黑，颧骨微高，粗手大脚，象是湘西乡下常见的庄稼汉子。\n");
        set("gender", "男性");
        set("age", 24);
        set("combat_exp", 1500000);
        set("str", 24);
        set("int", 15);
        set("dex", 18);
        set("con", 22);
        set("per", 28);
  
        set_skill("force", 200);
        set_skill("unarmed", 200);
        set_skill("dodge", 200);
        set_skill("blade", 200);
        set_skill("yanfly", 200);
        set_skill("shenzhaojing", 300);
        set_skill("xuedao-daofa", 200);
        map_skill("force", "shenzhaojing");
        map_skill("blade", "xuedao-daofa");
        map_skill("parry", "xuedao-daofa");
        map_skill("unarmed", "shenzhaojing");
        map_skill("dodge", "yanfly");
        set("inquiry", ([
                "水笙" : (: ask_me :),
        ]));
        set("wucan_count", 1);
        setup();
        carry_object("/clone/cloth/cloth")->wear();
        if (clonep())
        {
                weapon = new( WEAPON_DIR"treasure/xblade" );        
                if ( weapon->violate_unique() )
                {
                        destruct( weapon );
                        weapon = new( "/clone/weapon/gangdao" );
                }
                weapon->move(this_object());
                weapon->wield();
        }
} 

string ask_me()
{
        mapping fam; 
//      object ob;
        
        if (query("wucan_count") < 1)
                return "水笙姑娘？她在雪域等着我？";

        addn("wucan_count", -1);
        set_temp("marks/wucan", 1, this_player());
        return "水笙姑娘？她在雪域等着我？她有什么东西捎给我么？";
}
int accept_object(object who, object ob)
{
        object obj;
        if( query("id", ob) != "dachang" )
                return notify_fail("给我这东西有什么用？");
        message_vision("狄云笑着说道：“谢谢你！这位" + RANK_D->query_respect(ob) +"，辛苦你了。”\n", who);
        if( !query_temp("marks/wucan", who) )
        {
                return 1;
        }
        obj = new(ARMOR_DIR"treasure/wucanyi");
        delete_temp("marks/wucan", this_player());
        if ( obj->violate_unique() || uptime() < 300)
        {
                destruct( obj );
                return 1;
        }
        message_vision("狄云对$N说道：“这件乌蚕衣也不算是什么宝贝，聊表心意吧！”狄云从怀里掏出一团不起眼的东西，递到$N的手上。\n", who);
        obj->move(this_player());
        return 1;
}