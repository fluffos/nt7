// ouyang.h

int permit_recruit(object ob)
{
        object me = this_object();

        if( query("name", ob) == "欧阳锋" || 
            query("name", ob) == "欧阳克" )
        {
                message_vision("$N大怒：我操！你起这个名字是什么意思啊？\n",
                               this_object());
                return 0;
        }

/*
        if( query("born_family", ob) != "欧阳世家" && !query("reborn/times", ob) )
        {
                message_vision("$N对$n道：你不是我们欧阳家的人，我怎能收你为徒？\n",
                               me, ob);
                return 0;
        }
*/

        if( query("detach/欧阳世家", ob) || 
            query("betrayer/times", ob) )
        {
                message_vision("$N摇摇头对$n说：你反复无常，我不能收你为徒！\n",
                               me, ob);
                return 0;
        }

        if( query("family/family_name", ob) && 
            query("family/family_name", ob) != query("family/family_name", me) )
        {
                message_vision("$N对$n道：你虽然是欧阳家的人，但你入了其他门派，我不能收你为徒！\n",
                               me, ob);
                return 0;
        }

        return 1;
}
