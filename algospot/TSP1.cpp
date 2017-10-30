#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

vector<vector<long double>> tspTable;

long double minTsp(vector<vector<long double>> &graph, int currentNode, int currentDepth, int totalDepth, vector<bool> &visited, int currentKey)
{
	long double resultMin = -1.0;
	int n = graph.size();
	int key = (currentKey << 4) + currentNode;

	if(currentDepth == totalDepth)
		return 0.0;
	else
	{
		if(currentNode >= 0 && tspTable[currentNode][currentKey] > 0.0)
		{
			return tspTable[currentNode][currentKey];
		}
	}

	for(int idxNode = 0; idxNode < n; idxNode++)
	{
		if(currentNode == idxNode || visited[idxNode] == true)
			continue;

		long double tspValue;
		visited[idxNode] = true;
		tspValue = minTsp(graph, idxNode, currentDepth + 1, totalDepth, visited, currentKey + (1 << idxNode));
		if(currentNode >= 0)
			tspValue += graph[currentNode][idxNode];
		visited[idxNode] = false;
		if(resultMin < 0 || tspValue < resultMin)
			resultMin = tspValue;
	}

	if(currentNode >= 0)
		tspTable[currentNode][currentKey] = resultMin;

	return resultMin;
}

int main()
{
	std::ios::sync_with_stdio(false);

	int c, n;

	cin >> c;
	for(int idxCase = 0; idxCase < c; idxCase++)
	{
		vector<vector<long double>> graph;
		vector<bool> visited;
		cin >> n;

		graph.assign(n, vector<long double>(n, 0.0));
		visited.assign(n, false);
		tspTable.clear();
		tspTable.assign(20, vector<long double>(1 << 20, -1.0));
		for(int idxRow = 0; idxRow < n; idxRow++)
		{
			for(int idxCol = 0; idxCol < n; idxCol++)
			{
				cin >> graph[idxRow][idxCol];
			}
		}

		cout << fixed << setprecision(10);
		cout << minTsp(graph, -1, 0, n, visited, 0) << endl;
	}

	return 0;
}

/*
5
3
0.0000000000  611.6157225201  648.7500617289
611.6157225201  0.0000000000  743.8557967501
648.7500617289  743.8557967501  0.0000000000
4
0.0000000000  326.0008994586  503.1066076077  290.0250922998
326.0008994586  0.0000000000  225.1785728436  395.4019367384
503.1066076077  225.1785728436  0.0000000000  620.3945520632
290.0250922998  395.4019367384  620.3945520632  0.0000000000
8
0	7662.192509	558.0983633	7967.918368	6762.695403	8715.070202	2234.011701	7278.59996
6128.759477	0	4862.603618	9332.120436	4929.219632	371.1145161	3696.45602	78.50010531
9848.66297	3935.453476	0	1228.146716	2425.173733	5006.881887	3263.907901	1478.047631
1784.314732	1391.303112	5789.058527	0	8106.860491	5809.149855	5314.08025	4136.472794
3315.487985	1183.758096	9194.549257	9623.983168	0	545.5191252	315.8316316	7790.215567
3809.520845	5396.137797	1774.368312	6068.693121	2129.970907	0	4467.87248	3228.700358
738.0199501	3115.195108	4287.808864	2033.784289	8574.78612	4695.890759	0	8924.783833
5181.229175	6852.035973	159.7823495	4909.269494	6120.002775	786.4314902	7041.776343	0
15														
0	1087.871989	5160.32972	9211.863792	6053.383484	5246.551586	9302.788664	4658.819995	3101.590009	4130.480793	1586.422724	2344.2054	350.8315028	4596.353901	9928.509938
2464.553117	0	9517.748445	948.6104596	886.449486	4909.160275	7763.391187	9029.354694	7830.128118	7115.594349	3738.291168	9694.996314	7626.900961	7427.00713	7602.138771
6959.184202	1282.906463	0	7258.844323	1905.509885	6525.778808	4996.143446	2321.40507	7628.77709	3145.577424	9754.646156	9623.828008	2801.005178	6482.078783	5382.405863
4568.355275	2053.847217	8034.978455	0	8028.26393	9541.383038	2051.995168	8000.664128	3533.840085	8913.188182	4890.681119	1220.674557	2276.009415	7427.839135	6315.671806
9705.105736	1709.366661	7857.502044	740.4274121	0	1579.184767	5882.560119	2209.810781	3121.734576	4562.557711	7680.307856	417.9285669	5314.901231	344.3534433	5596.438424
5673.83475	3495.669559	752.6120306	2294.735656	6501.5707	0	3692.504069	6372.9641	2735.980765	9823.395957	3673.397989	6444.490022	9972.85422	922.5561802	6224.558462
9179.787662	9213.248387	2379.657313	5958.509991	8463.330126	6613.45267	0	945.2717105	3996.265878	9652.468429	1959.962081	114.9078081	5733.832823	7630.55745	1261.531628
6745.46701	5579.449562	5361.095625	5000.635885	4244.302219	7600.882428	9089.941482	0	5719.817595	1821.363987	6324.182467	2090.994467	5337.210198	8344.321247	622.949505
4784.478908	2972.075865	2079.252525	4872.967889	8173.784623	9364.738426	3973.187515	125.0175381	0	9696.210786	541.0176309	2463.622994	3839.924555	4932.9255	2771.087032
2355.391297	7549.804314	3817.268781	158.7027923	84.98723632	5971.295965	5538.346863	2355.221417	8611.003095	0	1618.597226	93.67991777	9852.160341	7493.22139	7035.51971
8421.098109	7920.689224	8192.905204	6888.374825	141.4107372	7614.975303	1769.540182	463.4406407	4106.618023	356.7738836	0	140.0192904	7660.644426	5836.37533	4757.44658
526.0562999	3984.012618	320.795314	2880.897709	4358.788535	8591.332453	8588.483022	2880.209134	3375.893045	4910.572922	4985.919918	0	9942.313044	5695.460824	9023.765538
8646.972643	4045.760884	1822.086577	3482.470378	1996.802431	4981.669349	6485.90733	1303.273468	5077.874075	3739.818286	9152.736127	6810.04433	0	43.62060016	2697.105617
2062.792309	2059.972255	4967.266026	191.0739136	9945.965318	631.0000041	9029.499337	9734.558748	4716.773207	1442.571811	9885.936728	2968.450923	6602.789993	0	4723.406971
8351.427229	4450.571675	9697.447245	1846.486265	2768.700795	1949.650086	984.2414289	30.82059641	7611.407645	3199.936819	6163.819921	825.6738228	6532.478666	2011.863996	0
20																			
0	1326.001424	7772.97369	7582.240232	2624.970191	8936.493992	7584.235016	6553.686044	5801.779519	3832.785842	4971.559617	6672.308507	1246.399727	4692.700863	2647.851247	4871.919018	6950.927212	7617.104723	9066.812566	6680.733531
4767.431076	0	1040.795872	9370.667919	3702.967112	3232.378532	2300.237991	5252.325836	2876.837572	9872.368737	7849.389526	8125.478377	612.3914064	46.50001968	3531.321458	6631.988042	850.9979675	240.8743704	9175.425212	6126.8005
3613.261324	4759.592502	0	3417.762364	4597.491279	6735.931426	6996.111648	5697.112881	7458.362905	9121.504157	6121.866616	3444.42643	1490.031114	9293.775638	5959.820097	7099.993853	9535.950146	1945.352689	1353.926551	7631.387413
6543.494708	3947.490631	3270.915034	0	2080.923082	697.8276004	9833.640498	6162.455887	2385.329559	8359.603757	2235.701588	2219.867735	465.0686269	9266.973157	8942.019813	7695.56818	4624.870269	8724.650644	922.452713	5007.82127
4401.49755	74.3726011	4251.527384	6009.297085	0	6137.405514	3211.633485	9206.50147	719.3539293	9321.18204	3688.572616	3191.905451	6214.973102	3240.090861	2194.148547	2250.034896	964.2244489	5382.768866	144.6020965	7820.8635
1297.333249	903.7296537	3444.293755	8005.964297	8941.431961	0	6360.859292	1085.476586	2888.323189	9607.870131	890.5588807	1419.962714	198.3562463	6661.502166	4897.418529	8328.936884	8617.98803	9172.818754	5343.110594	9034.144522
6724.567933	9621.807769	5434.961806	8684.032989	322.9349102	1005.67418	0	3861.19313	5406.864652	6265.730107	9054.116461	877.0745102	1322.29871	3521.518443	8943.371663	5960.382598	8709.262317	8311.128639	9662.372822	829.2978262
6708.403512	5770.262715	8276.980806	3019.037528	6954.085049	3157.092682	9730.161532	0	4514.081778	9820.89359	356.4693259	7356.507487	239.7252256	5004.117905	1486.721389	7818.539296	8332.142538	4047.337867	5480.46305	1268.249798
6579.349781	418.8918457	8964.168726	1059.789552	8109.904369	919.142803	9910.814407	775.551665	0	5204.366041	9214.289833	4836.308586	5231.143561	4165.719041	6463.113707	1220.08553	6574.423146	9066.105021	7515.251618	7372.463235
2128.664295	922.088676	5586.434134	5535.094061	4218.030801	862.0224499	6982.021281	6904.329188	488.4105383	0	987.3139196	8488.693795	4165.313638	8623.355616	6884.538623	7703.861066	3412.026343	7810.799758	1677.30635	2667.054758
7870.935286	536.223024	6279.203004	3167.131848	6000.201494	8538.063997	2963.106458	3008.346342	7972.852228	9449.861069	0	8798.977876	3956.304213	7086.632842	3158.822621	1160.623141	7309.635275	7189.94082	9666.876123	4954.057704
1195.788072	6975.021597	6780.597074	5326.369733	6046.769353	302.9570401	5127.803177	5993.046041	2664.674556	738.4583596	6079.846751	0	2847.281595	5649.607994	8213.542618	7407.041365	2953.457564	7267.319385	2536.762031	7003.763418
5103.853695	4729.550555	344.7622292	6342.560268	6140.406099	3233.619173	4152.65845	905.4677303	4179.364579	9382.914269	7791.338096	6691.349887	0	2160.261039	5531.709933	4786.655691	9795.78143	7027.774636	9430.984658	3906.675352
9016.251951	5761.838209	5715.058743	9993.105825	5208.502311	8449.493602	2591.753013	1837.605665	4856.202475	2534.379421	2689.43336	4499.17259	4268.279207	0	1065.32491	4189.584221	4357.43363	6429.477102	3877.018074	18.1717239
4707.250734	2389.094503	4185.133816	4698.707881	7942.043017	6172.997133	4180.715562	3099.343334	2711.570095	3352.961036	7653.549927	3879.501535	6759.710427	8559.893397	0	6367.031632	6087.987383	1048.851275	1206.838746	916.8654668
3933.588698	2195.393642	4397.94455	3030.3561	1055.843935	4103.317349	2214.009918	1300.37237	9259.490138	3943.463783	8099.595562	8767.861007	6104.66917	7876.568003	5130.430562	0	3636.816893	5967.560495	5730.420873	9810.737484
4309.017898	536.8057928	5768.507185	3108.516468	1204.057291	3727.881977	3319.167399	1055.505324	6879.671435	6017.40797	3050.265179	3928.729945	5273.535918	4262.251728	8513.591205	346.516881	0	7231.045484	9054.526405	3802.385553
893.0089566	2242.0553	4932.484709	6405.277635	5744.766728	2685.6819	3231.16133	113.7732625	4298.052035	335.9220789	4483.297013	3156.897894	4258.522899	3192.820343	5409.190795	4002.196509	8877.376312	0	3647.332153	5245.621347
9944.710106	7741.926097	6507.923938	6723.977478	7656.819701	7078.787158	6069.708229	8491.938267	4228.189631	2214.106598	3296.163822	5012.961647	5378.185198	9575.438398	5401.111715	5803.525704	8977.480492	9047.912106	0	309.5525538
7204.20796	1784.155325	294.9674418	4007.679778	3010.318427	202.6529361	1462.660677	3960.611437	1496.053696	5931.054889	2950.217841	5616.089821	2414.020252	6563.546628	2020.644688	7856.282126	7735.922183	3784.522203	9259.422557	0
*/