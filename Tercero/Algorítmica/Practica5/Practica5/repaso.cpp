void apply(){
	vector<vector<double> > E;
	vector<vector<int> > father;

	int nPointsDC = getDigitalcurve().getNumberPointsDigitalCurve();
	int nPointsA = getNumberPolygonalAproximation() + 1;

	//Reservo la memoria para las matrices

	E= vector<vector<double> >(nPointsDC, vector<double>(nPointsA));
	father= vector<vector<int> >(nPointsDC, vector<int>(nPointsA));





}