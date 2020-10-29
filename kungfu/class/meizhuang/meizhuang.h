// check recruit

int permit_recruit(object ob)
{
        command("say 梅庄暂不开放！");
        return 0;
        if( query("detach/梅庄", ob) || query("betrayer/梅庄", ob) )
        {
                command("say 你当年既然已经离开本庄，现在何必又要回来？");
                return 0;
        }

        if( query("betrayer/times", ob) )
        {
                command("say 我梅庄虽小，但是也不会接纳你这样的背信弃义之徒！");
                return 0;
        }

        if( query("family/family_name", ob) && 
            query("family/family_name", ob) != "梅庄" && 
            query("family/family_name", ob) != "日月神教" && 
            query("family/master_name", ob) != "东方不败" )
        {
                command("say 你既然已经有了名师指点，还来我们梅庄干嘛？");
                return 0;
        }

        return 1;
}
