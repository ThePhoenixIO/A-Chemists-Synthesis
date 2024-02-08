struct concentrationTable {
    float M1 = -1;
    float M2 = -1;
    float V1 = -1;
    float V2 = -1;
};

/*
* Function: concentrationCalc
* Arguments: concentrationTable calcTable, char calcVar
* Warnings: None
* Description: Calculates the missing variable in a concentration table
* Returns: The calculated value
*/
float concentrationCalc(concentrationTable calcTable, char calcVar) {
    switch (calcVar)
    {
        case 'M':
            if (calcTable.M2 == -1) {
                return (calcTable.M1 * calcTable.V1) / calcTable.V2;
            }
            else if (calcTable.M1 == -1){
                return (calcTable.M2 * calcTable.V2) / calcTable.V1;
            }
            else {
                return -1;
            }
        case 'V':
            if (calcTable.V2 > 0 ) {
                return (calcTable.M1 * calcTable.V1) / calcTable.M2;
            }
            else if (calcTable.V1 > 0){
                return (calcTable.M2 * calcTable.V2) / calcTable.M1;
            }
            else {
                return -1;
            }
        default:
            return -1;
}