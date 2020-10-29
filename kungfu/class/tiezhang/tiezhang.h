// check recruit

int permit_recruit(object ob)
{
        return notify_fail("暂时不开放。\n");
        if( query("detach/铁掌帮", ob) || query("betrayer/铁掌帮", ob) )
        {
                command("say 你当年既然已经离开本帮，现在干嘛又要回来？");
                return 0;
        }

        if( query("betrayer/times", ob) )
        {
                command("say 我铁掌帮虽然不是名门正派，但是你这样的背信弃义之徒还是不会要的！");
                return 0;
        }

        if( query("family/family_name", ob) && 
            query("family/family_name", ob) != "铁掌帮" && 
            query("family/family_name", ob) != "绝情谷" && 
            query("family/master_name", ob) != "裘千尺" )
        {
                command("say 你既然已经有了名师指点，还来我们铁掌帮干嘛？");
                return 0;
        }

        return 1;
}
