// riyue.h

int permit_recruit(object ob)
{
    object me;

    me = this_object();

    if( query("name", ob) == "东方不败" || 
        query("name", ob) == "任我行" )
    {
        message_vision("$N勃然大怒：哼！你也敢称我的讳号？\n",me);
        return 0;
    }

    if( query("detach/日月神教", ob) || 
        query("betrayer/times", ob) )
    {
        message_vision("$N大怒道：我日月神教岂能由你要来便来，要走便走？\n",me);
        return 0;
    }

    return 1;
}
