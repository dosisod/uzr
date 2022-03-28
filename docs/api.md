# API Endpoints

### `GET /health`

**Returns** `ok` with status code 200 if the server is up.

### `POST /login`

**Expected JSON**:

| Field | Type |
|-------|------|
| username | string |
| password | string |

**Returns** a `User` and 200 status on success.

**Returns** an error message and 401 status code upon invalid username/password.

### `POST /user/add`

**Expected JSON**:

| Field | Type |
|-------|------|
| username | string |
| password | string |
| fullName | string |
| phoneNumber | string |
| email | string |

**Returns** a `User` and 200 status upon successful creation.

**Returns** error message and 400 status code if field is missing, or user already exists.

### `GET /group/{id}`

**Expect** `id` to be an integer.

**Returns** a `Group` and 200 status code if group with id `id` is found.

**Returns** 404 status code if group exist.

## Schemas

### `User`

| Field | Type |
|-------|------|
| username | string |
| userId | integer |
| groupId | integer |

### `Group`

| Field | Type |
|-------|------|
| groupId | integer |
| name | string |
| members | string[] |
