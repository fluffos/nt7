// honghua.h

int permit_recruit(object ob)
{
        return notify_fail("暂时不开放。\n");
        if( query("detach/红花会", ob) || 
            query("betrayer/红花会", ob) )
        {
                command("say 我们红花会四大戒条你还记得吗？亏你还有脸回来！");
                return 0;
        }

        if( query("betrayer/times", ob) )
        {
                command("say 哼，阁下不忠不信，我们红花会可不会收留。");
                return 0;
        }

        if( query("family/family_name", ob) && 
            query("family/family_name", ob) != "红花会" )
        {
                command("say 阁下既有了师承，还来我们红花会做什么？");
                return 0;
        }

        return 1;
}
