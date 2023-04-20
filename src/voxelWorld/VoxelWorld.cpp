#include "VoxelWorld.h"

int getCubeIndex(int sideLength, int x, int y, int z)
{
    return x + sideLength * y + (sideLength * sideLength) * z;
}

VoxelWorld::VoxelWorld(unsigned char *voxels, int size, PointLight lightSource): lightSource(lightSource.getOrigin(), lightSource.getIntensity())
{
    float sizePower = std::log2(size);
    if (sizePower - (int)sizePower < 0.001 || sizePower - (int)sizePower > 0.999)
    {                                                       //check size is a power of 2
        int sideLength = std::cbrt(size);                   //N
        int sideLengthPower = round(std::log2(sideLength)); //n
        nPowers_int = new int[sideLength + 1];
        nPowers_float = new float[sideLength + 1];
        voxelTreeIndices = new int[sideLengthPower - 1];
        voxelTreeIndices[0] = 0;
        for (int i = 0; i < (sideLength + 1); i++)
        {
            nPowers_int[i] = pow(2, i);
            nPowers_float[i] = pow(2.0, i);
        }
        this->sideLengthPower = sideLengthPower;
        int treeSize = size;
        for (int i = sideLengthPower - 2; i >= 0; i--)
        {
            treeSize += pow(2, 3 * i);
        }
        voxelTree = new unsigned char[treeSize];
        for (int i = 0; i < size; i++)
        {
            voxelTree[i] = voxels[i];
        }
        int startIndex = 0;
        int endIndex = size; //size points to start of current boolean cube
        for (int i = sideLengthPower - 2; i >= 0; i--)
        {
            if (i == sideLengthPower - 2)
            {                                     //first boolean cube
                int boolCubeSize = pow(2, i + 1); //side length of boolean cube
                int boolCubeVol = pow(boolCubeSize, 3);
                bool *booleanCube = new bool[boolCubeVol];
                for (int x = 0; x < boolCubeSize; x++)
                {
                    for (int y = 0; y < boolCubeSize; y++)
                    {
                        for (int z = 0; z < boolCubeSize; z++)
                        {
                            int sum = 0;
                            sum += voxelTree[getCubeIndex(sideLength, 2 * x, 2 * y, 2 * z)];
                            sum += voxelTree[getCubeIndex(sideLength, 2 * x + 1, 2 * y, 2 * z)];
                            sum += voxelTree[getCubeIndex(sideLength, 2 * x, 2 * y + 1, 2 * z)];
                            sum += voxelTree[getCubeIndex(sideLength, 2 * x + 1, 2 * y + 1, 2 * z)];
                            sum += voxelTree[getCubeIndex(sideLength, 2 * x, 2 * y, 2 * z + 1)];
                            sum += voxelTree[getCubeIndex(sideLength, 2 * x + 1, 2 * y, 2 * z + 1)];
                            sum += voxelTree[getCubeIndex(sideLength, 2 * x, 2 * y + 1, 2 * z + 1)];
                            sum += voxelTree[getCubeIndex(sideLength, 2 * x + 1, 2 * y + 1, 2 * z + 1)];
                            booleanCube[getCubeIndex(boolCubeSize, x, y, z)] = sum > 0;
                        }
                    }
                }
                int byteCubeSize = pow(2, i); //side length of byte cube
                for (int x = 0; x < byteCubeSize; x++)
                {
                    for (int y = 0; y < byteCubeSize; y++)
                    {
                        for (int z = 0; z < byteCubeSize; z++)
                        {
                            unsigned char byteRepresentation = 0; //byte representing its 8 corresponding boolean vals
                            byteRepresentation += (unsigned char)booleanCube[getCubeIndex(boolCubeSize, 2 * x, 2 * y, 2 * z)];
                            byteRepresentation += (unsigned char)booleanCube[getCubeIndex(boolCubeSize, 2 * x + 1, 2 * y, 2 * z)] << 1;
                            byteRepresentation += (unsigned char)booleanCube[getCubeIndex(boolCubeSize, 2 * x, 2 * y + 1, 2 * z)] << 2;
                            byteRepresentation += (unsigned char)booleanCube[getCubeIndex(boolCubeSize, 2 * x + 1, 2 * y + 1, 2 * z)] << 3;
                            byteRepresentation += (unsigned char)booleanCube[getCubeIndex(boolCubeSize, 2 * x, 2 * y, 2 * z + 1)] << 4;
                            byteRepresentation += (unsigned char)booleanCube[getCubeIndex(boolCubeSize, 2 * x + 1, 2 * y, 2 * z + 1)] << 5;
                            byteRepresentation += (unsigned char)booleanCube[getCubeIndex(boolCubeSize, 2 * x, 2 * y + 1, 2 * z + 1)] << 6;
                            byteRepresentation += (unsigned char)booleanCube[getCubeIndex(boolCubeSize, 2 * x + 1, 2 * y + 1, 2 * z + 1)] << 7;
                            voxelTree[endIndex + getCubeIndex(byteCubeSize, x, y, z)] = byteRepresentation;
                        }
                    }
                }
                delete[] booleanCube;
                startIndex = endIndex;
                endIndex += pow(byteCubeSize, 3);
            }
            else
            {
                int boolCubeSize = pow(2, i + 1); //side length of boolean cube
                int boolCubeVol = pow(boolCubeSize, 3);
                bool *booleanCube = new bool[boolCubeVol];
                for (int x = 0; x < boolCubeSize; x++)
                {
                    for (int y = 0; y < boolCubeSize; y++)
                    {
                        for (int z = 0; z < boolCubeSize; z++)
                        {
                            booleanCube[getCubeIndex(boolCubeSize, x, y, z)] = voxelTree[startIndex + getCubeIndex(boolCubeSize, x, y, z)] > 0; //boolean cube at this level is same size as byte cube at previous level
                        }
                    }
                }
                //boolean cube now created
                int byteCubeSize = pow(2, i); //side length of byte cube
                for (int x = 0; x < byteCubeSize; x++)
                {
                    for (int y = 0; y < byteCubeSize; y++)
                    {
                        for (int z = 0; z < byteCubeSize; z++)
                        {
                            unsigned char byteRepresentation = 0; //byte representing its 8 corresponding boolean vals
                            byteRepresentation += (unsigned char)booleanCube[getCubeIndex(boolCubeSize, 2 * x, 2 * y, 2 * z)];
                            byteRepresentation += (unsigned char)booleanCube[getCubeIndex(boolCubeSize, 2 * x + 1, 2 * y, 2 * z)] << 1;
                            byteRepresentation += (unsigned char)booleanCube[getCubeIndex(boolCubeSize, 2 * x, 2 * y + 1, 2 * z)] << 2;
                            byteRepresentation += (unsigned char)booleanCube[getCubeIndex(boolCubeSize, 2 * x + 1, 2 * y + 1, 2 * z)] << 3;
                            byteRepresentation += (unsigned char)booleanCube[getCubeIndex(boolCubeSize, 2 * x, 2 * y, 2 * z + 1)] << 4;
                            byteRepresentation += (unsigned char)booleanCube[getCubeIndex(boolCubeSize, 2 * x + 1, 2 * y, 2 * z + 1)] << 5;
                            byteRepresentation += (unsigned char)booleanCube[getCubeIndex(boolCubeSize, 2 * x, 2 * y + 1, 2 * z + 1)] << 6;
                            byteRepresentation += (unsigned char)booleanCube[getCubeIndex(boolCubeSize, 2 * x + 1, 2 * y + 1, 2 * z + 1)] << 7;
                            voxelTree[endIndex + getCubeIndex(byteCubeSize, x, y, z)] = byteRepresentation;
                        }
                    }
                }
                delete[] booleanCube;
                startIndex = endIndex;
                endIndex += pow(byteCubeSize, 3);
            }
            voxelTreeIndices[sideLengthPower - 2 - i] = startIndex;
        }
    }
}

int VoxelWorld::getVoxelTreeIndex(int index) const
{
    return voxelTreeIndices[index];
}

VoxelWorld::~VoxelWorld()
{
    delete[] voxelTree;
    delete[] nPowers_float;
    delete[] nPowers_int;
}

unsigned char VoxelWorld::getVoxel(int index)
{
    return *(voxelTree + index);
}

int VoxelWorld::getSideLengthPower() const
{
    return sideLengthPower;
}

int VoxelWorld::getnPowersInt(int index) const
{
    return nPowers_int[index];
}

float VoxelWorld::getnPowersFloat(int index) const
{
    return nPowers_float[index];
}

bool VoxelWorld::intersectTopLevel(unsigned char *stack1, float *stack2, const Ray &ray, float &v0x, float &v0y, float &v0z, bool &foundIntersection, bool& inside, Vec &norm, unsigned char &voxelType) const
{
    inside = false;
    foundIntersection = false;
    stack1[0] = sideLengthPower;
    float px, py, pz;
    float dx, dy, dz;
    float X0, X1;
    float Y0, Y1;
    float Z0, Z1;
    px = ray.getOrigin().getElem(0);
    py = ray.getOrigin().getElem(1);
    pz = ray.getOrigin().getElem(2);
    dx = ray.getDirection().getElem(0);
    dy = ray.getDirection().getElem(1);
    dz = ray.getDirection().getElem(2);

    bool xFlipped, yFlipped, zFlipped; //bools to store if ray is going in neg direction for each axis
    xFlipped = false;
    yFlipped = false;
    zFlipped = false;

    if (dx >= 0)
    {
        X0 = 0;
        X1 = nPowers_int[sideLengthPower];
    }
    else
    {
        X1 = 0;
        X0 = nPowers_int[sideLengthPower];
        xFlipped = true;
    }

    if (dy >= 0)
    {
        Y0 = 0;
        Y1 = nPowers_int[sideLengthPower];
    }
    else
    {
        Y1 = 0;
        Y0 = nPowers_int[sideLengthPower];
        yFlipped = true;
    }

    if (dz >= 0)
    {
        Z0 = 0;
        Z1 = nPowers_int[sideLengthPower];
    }
    else
    {
        Z1 = 0;
        Z0 = nPowers_int[sideLengthPower];
        zFlipped = true;
    }

    float tx0, ty0, tz0;
    float tx1, ty1, tz1;

    tx0 = (X0 - px) / dx;
    ty0 = (Y0 - py) / dy;
    tz0 = (Z0 - pz) / dz;

    tx1 = (X1 - px) / dx;
    ty1 = (Y1 - py) / dy;
    tz1 = (Z1 - pz) / dz;

    float tMax, tMin;

    if (tx1 <= ty1 && tx1 <= tz1)
    {
        tMax = tx1;
    }
    else if (ty1 <= tx1 && ty1 <= tz1)
    {
        tMax = ty1;
    }
    else if (tz1 <= tx1 && tz1 <= ty1)
    {
        tMax = tz1;
    }

    unsigned char entryPlane;
    if (tx0 >= ty0 && tx0 >= tz0)
    {
        entryPlane = 1;
        tMin = tx0;
        if (tx0 > tMax || tMax < 0)
        {
            return false;
        }
    }
    else if (ty0 >= tx0 && ty0 >= tz0)
    {
        entryPlane = 2;
        tMin = ty0;
        if (ty0 > tMax || tMax < 0)
        {
            return false;
        }
    }
    else
    {
        entryPlane = 4;
        tMin = tz0;
        if (tz0 > tMax || tMax < 0)
        {
            return false;
        }
    }

    if (tMin < 0)
    { //in this case, we know we're inside the voxel cube as we know tMax > 0
        inside = true;
        float currentMinX = 0;
        float currentMinY = 0;
        float currentMinZ = 0;

        float tempMinX, tempMinY, tempMinZ;
        for (int i = 0; i < sideLengthPower; i++)
        {
            stack1[i * 3] = sideLengthPower - i;
            stack1[(i * 3) + 1] = 0;
            tempMinX = currentMinX + nPowers_float[sideLengthPower - 1 - i];
            if (px >= tempMinX)
            {
                stack1[(i * 3) + 1] += 1;
                currentMinX = tempMinX;
            }
            tempMinY = currentMinY + nPowers_float[sideLengthPower - 1 - i];
            if (py >= tempMinY)
            {
                stack1[(i * 3) + 1] += 2;
                currentMinY = tempMinY;
            }
            tempMinZ = currentMinZ + nPowers_float[sideLengthPower - 1 - i];
            if (pz >= tempMinZ)
            {
                stack1[(i * 3) + 1] += 4;
                currentMinZ = tempMinZ;
            }
            stack2[3*i] = currentMinX;
            stack2[(3*i)+1] = currentMinY;
            stack2[(3*i)+2] = currentMinZ;
        }
        int x, y, z, voxelTreeIndex;
        x = std::round(currentMinX);
        y = std::round(currentMinY);
        z = std::round(currentMinZ);
        voxelTreeIndex = nPowers_int[2 * sideLengthPower] * z;
        voxelTreeIndex += nPowers_int[sideLengthPower] * y;
        voxelTreeIndex += x;
        voxelType = voxelTree[voxelTreeIndex];
        if (voxelType == 0)
        {
            foundIntersection = false;
            return true;
        }
        else
        {
            foundIntersection = true;
            if (xFlipped)
            {
                X0 = currentMinX + 1;
                X1 = currentMinX;
            }
            else
            {
                X0 = currentMinX;
                X1 = currentMinX + 1;
            }

            if (yFlipped)
            {
                Y0 = currentMinY + 1;
                Y1 = currentMinY;
            }
            else
            {
                Y0 = currentMinY;
                Y1 = currentMinY + 1;
            }

            if (zFlipped)
            {
                Z0 = currentMinZ + 1;
                Z1 = currentMinZ;
            }
            else
            {
                Z0 = currentMinZ;
                Z1 = currentMinZ + 1;
            }

            tx1 = (X1 - px) / dx;
            ty1 = (Y1 - py) / dy;
            tz1 = (Z1 - pz) / dz;

            float tMax;

            unsigned char exitPlane;

            if (tx1 <= ty1 && tx1 <= tz1)
            {
                tMax = tx1;
                if (xFlipped)
                {
                    exitPlane = 9;
                }
                else
                {
                    exitPlane = 1;
                }
            }
            else if (ty1 <= tx1 && ty1 <= tz1)
            {
                tMax = ty1;
                if (yFlipped)
                {
                    exitPlane = 10;
                }
                else
                {
                    exitPlane = 2;
                }
            }
            else if (tz1 <= tx1 && tz1 <= ty1)
            {
                tMax = tz1;
                if (zFlipped)
                {
                    exitPlane = 12;
                }
                else
                {
                    exitPlane = 4;
                }
            }
            v0x = px + (tMax * dx);
            v0y = py + (tMax * dy);
            v0z = pz + (tMax * dz);

            switch (exitPlane)
            { //entry plane
            case 1:
                norm = Vec(-1, 0, 0);
                break;

            case 2:
                norm = Vec(0, -1, 0);
                break;

            case 4:
                norm = Vec(0, 0, -1);
                break;

            case 9:
                norm = Vec(1, 0, 0);
                break;

            case 10:
                norm = Vec(0, 1, 0);
                break;

            case 12:
                norm = Vec(0, 0, 1);
                break;

            default:
                break;
            }
            return true;
        }
    }

    if (entryPlane == 1 && xFlipped)
    {
        stack1[2] = 9; //4th bit determines whether plane is X0 or X1
    }
    else if (entryPlane == 2 && yFlipped)
    {
        stack1[2] = 10;
    }
    else if (entryPlane == 4 && zFlipped)
    {
        stack1[2] = 12;
    }
    else
    {
        stack1[2] = entryPlane;
    }

    stack1[1] = 0; //ensure index position starts as 0

    stack2[0] = 0;
    stack2[1] = 0;
    stack2[2] = 0;

    if (entryPlane == 1)
    { //Storing which is the entry plane means we can avoid calculating one of v0x, v0y, v0z and the issue of rounding the v0 value of the intersection plane
        if (xFlipped)
        {
            stack1[1] = 1;
            stack2[0] = nPowers_float[sideLengthPower - 1];
        }
        v0y = py + (tx0 * dy);
        if (v0y >= nPowers_float[sideLengthPower - 1])
        {
            stack1[1] += 2;
            stack2[1] = nPowers_float[sideLengthPower - 1];
        }
        v0z = pz + (tx0 * dz);
        if (v0z >= nPowers_float[sideLengthPower - 1])
        {
            stack1[1] += 4;
            stack2[2] = nPowers_float[sideLengthPower - 1];
        }

        return true;
    }
    else if (entryPlane == 2)
    {
        if (yFlipped)
        {
            stack1[1] = 2;
            stack2[1] = nPowers_float[sideLengthPower - 1];
        }
        v0x = px + (ty0 * dx);
        if (v0x >= nPowers_float[sideLengthPower - 1])
        {
            stack1[1] += 1;
            stack2[0] = nPowers_float[sideLengthPower - 1];
        }
        v0z = pz + (ty0 * dz);
        if (v0z >= nPowers_float[sideLengthPower - 1])
        {
            stack1[1] += 4;
            stack2[2] = nPowers_float[sideLengthPower - 1];
        }
        return true;
    }
    else
    {
        if (zFlipped)
        {
            stack1[1] = 4;
            stack2[2] = nPowers_float[sideLengthPower - 1];
        }
        v0x = px + (tz0 * dx);
        if (v0x >= nPowers_float[sideLengthPower - 1])
        {
            stack1[1] += 1;
            stack2[0] = nPowers_float[sideLengthPower - 1];
        }
        v0y = py + (tz0 * dy);
        if (v0y >= nPowers_float[sideLengthPower - 1])
        {
            stack1[1] += 2;
            stack2[1] = nPowers_float[sideLengthPower - 1];
        }
        return true;
    }
}

bool VoxelWorld::getNextNeighbour(unsigned char *stack1, float *stack2, const Ray &ray, float &v0x, float &v0y, float &v0z, int &parentScale) const
{
    int scaleIndex = (sideLengthPower - parentScale) * 3;
    int scaleMinus1 = parentScale - 1;
    float px, py, pz;
    float dx, dy, dz;
    float X0, X1;
    float Y0, Y1;
    float Z0, Z1;
    px = ray.getOrigin().getElem(0);
    py = ray.getOrigin().getElem(1);
    pz = ray.getOrigin().getElem(2);
    dx = ray.getDirection().getElem(0);
    dy = ray.getDirection().getElem(1);
    dz = ray.getDirection().getElem(2);

    bool xFlipped, yFlipped, zFlipped; //bools to store if ray is going in neg direction for each axis
    xFlipped = false;
    yFlipped = false;
    zFlipped = false;

    if (dx >= 0)
    {
        X0 = stack2[scaleIndex];
        X1 = stack2[scaleIndex] + nPowers_float[scaleMinus1];
    }
    else
    {
        X1 = stack2[scaleIndex];
        X0 = stack2[scaleIndex] + nPowers_float[scaleMinus1];
        xFlipped = true;
    }

    if (dy >= 0)
    {
        Y0 = stack2[scaleIndex + 1];
        Y1 = stack2[scaleIndex + 1] + nPowers_float[scaleMinus1];
    }
    else
    {
        Y1 = stack2[scaleIndex + 1];
        Y0 = stack2[scaleIndex + 1] + nPowers_float[scaleMinus1];
        yFlipped = true;
    }

    if (dz >= 0)
    {
        Z0 = stack2[scaleIndex + 2];
        Z1 = stack2[scaleIndex + 2] + nPowers_float[scaleMinus1];
    }
    else
    {
        Z1 = stack2[scaleIndex + 2];
        Z0 = stack2[scaleIndex + 2] + nPowers_float[scaleMinus1];
        zFlipped = true;
    }

    float tx1, ty1, tz1;

    tx1 = X1 - px;
    if (tx1 == 0)
    { //sorts out 0/0 errors
        tx1 = (tx1 - 0.0001) / dx;
    }
    else
    {
        tx1 = tx1 / dx;
    }
    ty1 = Y1 - py;
    if (ty1 == 0)
    {
        ty1 = (ty1 - 0.0001) / dy;
    }
    else
    {
        ty1 = ty1 / dy;
    }
    tz1 = Z1 - pz;
    if (tz1 == 0)
    {
        tz1 = (tz1 - 0.0001) / dz;
    }
    else
    {
        tz1 = tz1 / dz;
    }

    float tMax;

    unsigned char exitPlane;

    if (tx1 <= ty1 && tx1 <= tz1)
    {
        tMax = tx1;
        exitPlane = 1;
        if (xFlipped)
        {
            exitPlane += 8;
        }
    }
    else if (ty1 <= tx1 && ty1 <= tz1)
    {
        tMax = ty1;
        exitPlane = 2;
        if (yFlipped)
        {
            exitPlane += 8;
        }
    }
    else
    {
        tMax = tz1;
        exitPlane = 4;
        if (zFlipped)
        {
            exitPlane += 8;
        }
    }

    v0x = (tMax * dx) + px;
    v0y = (tMax * dy) + py;
    v0z = (tMax * dz) + pz;

    bool foundCube = false;
    for (scaleIndex; scaleIndex >= 0; scaleIndex -= 3)
    {
        if ((exitPlane & 8) == 0)
        { //Pos exit plane
            if ((exitPlane & stack1[scaleIndex + 1]) == 0)
            { //still in same parent cube
                foundCube = true;
                stack1[scaleIndex + 1] += exitPlane; //Set index, don't need to set 4th bit to 0 as it we know it is if at this point
                stack1[scaleIndex + 2] = exitPlane;  //set entry plane
                if ((exitPlane & 1) != 0)
                { //moving in x direction
                    stack2[scaleIndex] += nPowers_float[stack1[scaleIndex] - 1];
                }
                else if ((exitPlane & 2) != 0)
                { //moving in y direction
                    stack2[scaleIndex + 1] += nPowers_float[stack1[scaleIndex] - 1];
                }
                else
                { //moving in z direction
                    stack2[scaleIndex + 2] += nPowers_float[stack1[scaleIndex] - 1];
                }
                break;
            }
        }
        else
        { //neg exit plane
            if ((exitPlane & stack1[scaleIndex + 1]) != 0)
            { //staying in parent cube
                foundCube = true;
                stack1[scaleIndex + 1] -= (exitPlane & 247); //set index, & operation sets 4th bit to 0
                stack1[scaleIndex + 2] = exitPlane;          //set entry plane
                if ((exitPlane & 1) != 0)
                { //moving in x direction
                    stack2[scaleIndex] -= nPowers_float[stack1[scaleIndex] - 1];
                }
                else if ((exitPlane & 2) != 0)
                { //moving in y direction
                    stack2[scaleIndex + 1] -= nPowers_float[stack1[scaleIndex] - 1];
                }
                else
                { //moving in z direction
                    stack2[scaleIndex + 2] -= nPowers_float[stack1[scaleIndex] - 1];
                }
                break;
            }
        }
    }
    parentScale = stack1[scaleIndex];
    return foundCube;
}

void VoxelWorld::getChild(unsigned char *stack1, float *stack2, const Ray &ray, float &v0x, float &v0y, float &v0z, int &parentScale) const
{
    int scaleIndex = (sideLengthPower - parentScale) * 3;
    unsigned char entryPlane = stack1[scaleIndex + 2];
    unsigned char index = 0;
    float X0, Y0, Z0;
    float halfSideLen = nPowers_float[parentScale - 2];
    X0 = stack2[scaleIndex];
    Y0 = stack2[scaleIndex + 1];
    Z0 = stack2[scaleIndex + 2];
    stack2[scaleIndex + 3] = X0;
    stack2[scaleIndex + 4] = Y0;
    stack2[scaleIndex + 5] = Z0;
    if ((entryPlane & 8) == 0)
    { //direction not reversed
        if (entryPlane == 1)
        { //entering through first x-plane so x index is 0
            if (v0y > (Y0 + halfSideLen))
            {
                index = 2;
                stack2[scaleIndex + 4] = Y0 + halfSideLen;
            }
            if (v0z > (Z0 + halfSideLen))
            {
                index = (index | 4); //bitwise or here adds 4 (we know the 3rd bit is 0)
                stack2[scaleIndex + 5] = Z0 + halfSideLen;
            }
        }
        else if (entryPlane == 2)
        { //entering through first y-plane so y index is 0
            if (v0x > (X0 + halfSideLen))
            {
                index = 1;
                stack2[scaleIndex + 3] = X0 + halfSideLen;
            }
            if (v0z > (Z0 + halfSideLen))
            {
                index = (index | 4); //bitwise or here adds 4 (we know the 3rd bit is 0)
                stack2[scaleIndex + 5] = Z0 + halfSideLen;
            }
        }
        else
        {
            if (v0x > (X0 + halfSideLen))
            {
                index = 1;
                stack2[scaleIndex + 3] = X0 + halfSideLen;
            }
            if (v0y > (Y0 + halfSideLen))
            {
                index = (index | 2);
                stack2[scaleIndex + 4] = Y0 + halfSideLen;
            }
        }
    }
    else
    { //direction reversed
        if (entryPlane == 9)
        { //entering through second x-plane so x index is 1
            stack2[scaleIndex + 3] = X0 + halfSideLen;
            index = 1;
            if (v0y > (Y0 + halfSideLen))
            {
                index = (index | 2);
                stack2[scaleIndex + 4] = Y0 + halfSideLen;
            }
            if (v0z > (Z0 + halfSideLen))
            {
                index = (index | 4); //bitwise or here adds 4 (we know the 3rd bit is 0)
                stack2[scaleIndex + 5] = Z0 + halfSideLen;
            }
        }
        else if (entryPlane == 10)
        { //entering through second y-plane so y index is 2
            stack2[scaleIndex + 4] = Y0 + halfSideLen;
            index = 2;
            if (v0x > (X0 + halfSideLen))
            {
                index = (index | 1);
                stack2[scaleIndex + 3] = X0 + halfSideLen;
            }
            if (v0z > (Z0 + halfSideLen))
            {
                index = (index | 4); //bitwise or here adds 4 (we know the 3rd bit is 0)
                stack2[scaleIndex + 5] = Z0 + halfSideLen;
            }
        }
        else
        { //entering through second z axis
            stack2[scaleIndex + 5] = Z0 + halfSideLen;
            index = 4;
            if (v0x > (X0 + halfSideLen))
            {
                index = (index | 1);
                stack2[scaleIndex + 3] = X0 + halfSideLen;
            }
            if (v0y > (Y0 + halfSideLen))
            {
                index = (index | 2);
                stack2[scaleIndex + 4] = Y0 + halfSideLen;
            }
        }
    }
    stack1[scaleIndex + 3] = parentScale - 1;
    stack1[scaleIndex + 4] = index;
    stack1[scaleIndex + 5] = entryPlane; //this doesn't change
    parentScale--;
}

bool VoxelWorld::intersect(const Ray &ray, unsigned char &voxelType, Point &point, Vec &norm) const
{
    unsigned char stack1[sideLengthPower * 3];
    float stack2[sideLengthPower * 3];
    float v0x, v0y, v0z;
    int currentParentScale = sideLengthPower;
    int currentScaleIndex = 0;
    int currentScaleIndexNorm = 0;
    bool isNext;
    bool isEmpty;
    bool foundValidCube = false;
    int byteCubeIndex;
    int relativeIndex;
    unsigned int x, y, z;
    int count = 0;
    bool inside;
    if (intersectTopLevel(stack1, stack2, ray, v0x, v0y, v0z, foundValidCube, inside, norm, voxelType))
    {
        if (!foundValidCube)
        {
            if(inside) {
                currentParentScale = 1;
                currentScaleIndex = (sideLengthPower - 1) * 3;
            }
            while (!foundValidCube)
            {
                if (currentParentScale == 1)
                {
                    x = std::round(stack2[currentScaleIndex]);
                    y = std::round(stack2[currentScaleIndex + 1]);
                    z = std::round(stack2[currentScaleIndex + 2]);
                    byteCubeIndex = nPowers_int[2 * sideLengthPower] * z;
                    byteCubeIndex += nPowers_int[sideLengthPower] * y;
                    byteCubeIndex += x;
                    isEmpty = voxelTree[byteCubeIndex] == 0;
                    if (isEmpty)
                    {
                        isNext = getNextNeighbour(stack1, stack2, ray, v0x, v0y, v0z, currentParentScale);
                        currentScaleIndex = (sideLengthPower - currentParentScale) * 3;
                        if(!isNext) {
                            return false;
                        }
                    }
                    else
                    {
                        voxelType = voxelTree[byteCubeIndex];
                        foundValidCube = true;
                    }
                }
                else
                {
                    byteCubeIndex = voxelTreeIndices[currentParentScale - 2];
                    int divFactor = nPowers_int[currentParentScale];
                    x = std::round(stack2[currentScaleIndex]);
                    x = x >> currentParentScale;
                    y = std::round(stack2[currentScaleIndex + 1]);
                    y = y >> currentParentScale;
                    z = std::round(stack2[currentScaleIndex + 2]);
                    z = z >> currentParentScale; //these are byte cube coords
                    byteCubeIndex += nPowers_int[2 * (sideLengthPower - currentParentScale)] * z;
                    byteCubeIndex += nPowers_int[sideLengthPower - currentParentScale] * y;
                    byteCubeIndex += x;
                    isEmpty = ((voxelTree[byteCubeIndex] & (1 << stack1[currentScaleIndex + 1])) == 0);
                    if (isEmpty)
                    {
                        isNext = getNextNeighbour(stack1, stack2, ray, v0x, v0y, v0z, currentParentScale);
                        if (!isNext)
                        {
                            return false; //got to end of top-level cube
                        }
                        currentScaleIndex = (sideLengthPower - currentParentScale) * 3;
                    }
                    else
                    {
                        getChild(stack1, stack2, ray, v0x, v0y, v0z, currentParentScale);
                        currentScaleIndex += 3;
                    }
                }
            }
            switch (stack1[currentScaleIndex + 2])
            { //entry plane
            case 1:
                norm = Vec(-1, 0, 0);
                break;

            case 2:
                norm = Vec(0, -1, 0);
                break;

            case 4:
                norm = Vec(0, 0, -1);
                break;

            case 9:
                norm = Vec(1, 0, 0);
                break;

            case 10:
                norm = Vec(0, 1, 0);
                break;

            case 12:
                norm = Vec(0, 0, 1);
                break;

            default:
                break;
            }
        }

        point = Point(v0x, v0y, v0z);
        return true;
    }
    return false;
}

IntersectionSpec VoxelWorld::getIntersection(const Ray& ray) const {
    Point point;
    Vec norm;
    unsigned char voxelType;
    bool hit = intersect(ray, voxelType, point, norm);
    if(!hit) {
        return IntersectionSpec(false, norm, point, 0, 0, 0, 0, 0, 0, 0, 0, Colour(0, 0, 0), Vec(0, 0, 0), Colour(0, 0, 0), false);
    }
    Vec lightVec = lightSource.getOrigin() - point;
    lightVec.normalize();
    return IntersectionSpec(hit,
                            norm,
                            point,
                            0.2,
                            0.8,
                            0.7,
                            100,
                            1,
                            1.3,
                            0,
                            0,
                            Colour(0.1, 0.3, 0.8),
                            lightVec,
                            lightSource.getIntensity(),
                            false);
}