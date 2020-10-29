// check recruit

int permit_recruit(object ob)
{
        if( query("detach/密宗", ob) || query("betrayer/密宗", ob) )
        {
                command("say 你离开了密宗们，密宗已经不认你了！");
                return 0;
        }

        if( query("betrayer/times", ob) )
        {
                command("say 我们密宗最恨判师之徒，你还不快滚？");
                return 0;
        }

        if( query("family/family_name", ob) && 
            query("family/family_name", ob) != "密宗" )
        {
                command("say 你有师傅指点，当循序渐进，怎可贸然判师？");
                return 0;
        }

        return 1;
}
