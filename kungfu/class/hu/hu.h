int permit_recruit(object ob)
{
        if( query("detach/关外胡家", ob) || query("betrayer/关外胡家", ob) )
        {
                command("say 你反复无常，我不能收你为徒！");
                return 0;
        }

/*
        if( query("born_family", ob) != "关外胡家" && !query("reborn/times", ob) )
        {
                command("hmm");
                command("say 我关外胡家虽然人丁稀少，但也不收纳族外之人。");
                return 0;
        }
*/

        if( query("family/family_name", ob) && 
            query("family/family_name", ob) != "关外胡家" )
        {
                command("hmm");
                command("say 你既然已经离家拜师，就应有所作为，又跑回来作甚？");
                return 0;
        }

        return 1;
}
