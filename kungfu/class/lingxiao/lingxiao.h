// check recruit

int permit_recruit(object ob)
{
        return notify_fail("暂时不开放。\n");
        if( query("detach/凌霄城", ob) || query("betrayer/凌霄城", ob) )
        {
                command("say 你当年既然已经离开凌霄城，现在何必又要回来？");
                return 0;
        }

        if( query("betrayer/times", ob) )
        {
                command("say 我们雪山凌霄城最狠就是你这样的背信弃义之徒！");
                return 0;
        }

        if( query("family/family_name", ob) && 
            query("family/family_name", ob) != "凌霄城" && 
            query("family/family_name", ob) != "玄素庄" && 
            query("family/master_name", ob) != "石清" )
        {
                command("say 你既然已经有了名师指点，还来我们雪山剑派干嘛？");
                return 0;
        }

        return 1;
}
