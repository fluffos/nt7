// check recruit

int permit_recruit(object ob)
{
        if( query("detach/全真教", ob) || query("betrayer/全真教", ob) )
        {
                command("say 你当年既然离开全真教，何必又要回来？");
                return 0;
        }

        if( query("betrayer/times", ob) )
        {
                command("say 我们全真教乃名门正派，决不收判师之徒！");
                return 0;
        }

        if( query("family/family_name", ob) && 
            query("family/family_name", ob) != "全真教" )
        {
                command("say 你既然已经有了名师指点，不好好学习，来我们全真教作甚？");
                return 0;
        }

        return 1;
}
