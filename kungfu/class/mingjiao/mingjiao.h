// MingJiao.h for all npc of mingjiao

int permit_recruit(object ob)
{
        if( query("detach/明教", ob) || 
            query("betrayer/明教", ob) )
        {
                command("say 离开了明教就不要再回来！");
                return 0;
        }

        if( query("betrayer/times", ob) )
        {
                command("say 阁下不忠不信，我们明教最恨的就是你这种人。");
                return 0;
        }

        if( query("family/family_name", ob) && 
            query("family/family_name", ob) != "明教" )
        {
                command("say 你有了师傅，就不要来我们明教了！");
                return 0;
        }

        return 1;
}

/*
int recognize_apprentice(object ob, string skill)
{
        object me = this_object();
        mapping ob_fam;

        if( !(ob_fam=query("family", ob)) || ob_fam["family_name"] != "明教" )
        {
                command("say " + RANK_D->query_respect(ob) + "与本教素无来往，不知此话从何谈起？");
                return -1;
        }

        if( ob_fam["generation"] <= query("family/generation", me) )
        {
                return 1;
        }

        return 0;
}
*/
