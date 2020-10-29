string *food_name = ({
"翡翠烧卖", "鸭菜包子", "千层油糕", "芝麻包子", 
});

string ask_secret()
{
    string food =  food_name[ random( sizeof( food_name ) ) ];
    command( "en" );
    command( "think" );
    command("tell"+query("id", this_player())+
        " 你帮我买个" + food );
    set_temp("kid_ask/"+query("id"), food, this_player());
    return "怎么样？帮我买了，我就告诉你！\n";
}

int accept_object( object me, object ob)
{
    string food,id=query("id", me);
    food=query_temp("kid_ask/"+query("id", me));
    if ( food && food == ob->name() )
    {
        command( "grin " + id );
        command( "tell " + id + " 我的秘密是：我老爸叫" 
        + query( "papa_name" ) + "。" );
        command( "laugh1 " + id );
        delete_temp("kid_ask/"+query("id"), me);
        return 1;
    }
    command( "look " + id );
    command( "sigh " + id );
    return 0;
}
